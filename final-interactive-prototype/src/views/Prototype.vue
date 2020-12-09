<template>
  <div class="prototype-view">
    <img :src="require(`@/assets/bg-library.png`)" alt="" class="bg">
    <div class="search-bar">
      <v-autocomplete
        prepend-icon="mdi-search"
        rounded
        solo
        full-width
        placeholder="I am going to..."
      ></v-autocomplete>
    </div>
    <div class="info-block">
      <div class="location-name">{{ currentLocation }}</div>
      <div class="data-point-from-time">{{sensorDataFromNow}}, {{ sensorDataTime }}</div>
      <div v-if="testCase === 1">
        <div class="big-temp-title">Current temperature</div>
        <div class="big-temp">{{ currentSensorTemp }}℃</div>
        <div class="small-temp">You feel like {{ myBodyTemp }}℃</div>
      </div>
      <div v-else>
        <div class="big-temp-title">Body temperature</div>
        <div class="big-temp">{{ myBodyTemp }}℃</div>
        <div class="small-temp">
          Actual temperature is {{ currentSensorTemp }}℃
        </div>
      </div>
    </div>
    <div class="avtar-block">
      <img :src="require(`@/assets/${avtarUrl}`)" alt="" />
    </div>
    <div class="bottom-block mb-5">
      <div class="msg-block">
        {{ greetingText }}
      </div>
      <div class="feeling-btn" @click="toggleBottomSheet">+</div>
    </div>
    <v-bottom-sheet v-model="isBottomSheet">
      <v-sheet class="text-center" height="200px">
        <div class="my-3 pt-5">How do you feel now?</div>
        <v-row justify="space-between" class="mx-3">
          <img
            class="feeling-inner-btn"
            :src="require(`@/assets/button-${genderPrefix}-cold.png`)"
            alt=""
            @click="userAdjustment(-1)"
          />
          <img
            class="feeling-inner-btn"
            :src="require(`@/assets/button-${genderPrefix}-good.png`)"
            alt=""
            @click="userAdjustment(0)"
          />
          <img
            class="feeling-inner-btn"
            :src="require(`@/assets/button-${genderPrefix}-hot.png`)"
            alt=""
            @click="userAdjustment(1)"
          />
        </v-row>
      </v-sheet>
    </v-bottom-sheet>
    <div class="feedback-thankyou-view" v-if="isFeedback">
      <img :src="require('@/assets/feedback_thankyou.png')" alt="">
    </div>
  </div>
</template>

<script>
import moment from "moment";

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms || 1000));
}
export default {
  name: "PrototypeView",
  props: {
    username: String,
    gender: String,
    feelingTendance: String,
    weighting: {
      type: Number,
      default: 0,
    },
    testCase: {
      type: Number,
      default: 1,
    },
  },
  mqtt: {
    'sensor-update': function(data) {
      let _msg = JSON.parse(data)
      this.currentSensorTemp = Math.round(_msg.res.temperature* 10)/10
      this.currentSensorTimestamp = _msg.timestamp

    }
  },
  mounted() {
    this.$mqtt.subscribe('sensor-update')
    this.setCurrentTime();
    this.currentTimer = setInterval(this.setCurrentTime(), 1000);
    if (this.feelingTendance === "Fear cold"){
      this.userFeedbackAdjustment = -2
    } else if (this.feelingTendance === "Fear hot"){
      this.userFeedbackAdjustment = 2
    }
  },
  watch: {
    async isFeedback() {
      if (this.isFeedback){
        await sleep(4000);
        this.isFeedback = false
      }
    }
  },
  computed: {
    greetingText() {
      return `Hi ${this.username}, according to our sensors data and your perferences, here is our suggestion for your outfit for today. ${(this.myBodyTemp < 20 && this.myBodyTemp > 17)?'Bring a jacket with you maybe a good choice~':''}`;
    },
    myBodyTemp() {
      return (
        this.currentSensorTemp + this.weighting + this.userFeedbackAdjustment
      );
    },
    genderPrefix() {
      return this.gender === "Male" ? "boy" : "girl";
    },
    avtarUrl() {
      let _gender = this.gender === "Male" ? "boy" : "girl";
      let _feeling = "normal";
      if (this.myBodyTemp > 28) {
        _feeling = "hot";
      } else if (this.myBodyTemp < 17) {
        _feeling = "cold";
      }
      return `${_gender}-${_feeling}.png`;
    },
    sensorDataTime() {
      return moment(this.currentSensorTimestamp).format(`h:mm a`)
    },
    sensorDataFromNow() {
      return moment(this.currentSensorTimestamp).fromNow()
    }
  },
  data() {
    return {
      currentTime: null,
      currentTimer: null,
      currentLocation: "Pao Yue-kong Library",
      currentSensorTemp: 21.2,
      currentSensorTimestamp: null,
      userFeedbackAdjustment: 0,
      isBottomSheet: false,
      isFeedback: false
    };
  },
  methods: {
    setCurrentTime() {
      this.currentTime = moment().format(`h:mm a`);
    },
    toggleBottomSheet() {
      this.isBottomSheet = !this.isBottomSheet;
    },
    userAdjustment(adj) {
      this.userFeedbackAdjustment += adj;
      this.isBottomSheet = false
      this.isFeedback = true
      console.log(this.userFeedbackAdjustment);
    },
  },
};
</script>

<style>
.prototype-view {
  width: 100vw;
  height: 100vh;
  background-color: black;
  display: flex;
  flex-direction: column;
  align-items: center;
  position: relative;
}
.prototype-view > div {
  position: relative;
  z-index: 1;
}
.prototype-view > .bg{
  width: 100vw;
  height: inherit;
  object-fit: cover;
  position: absolute;
  top: 0;
}
.search-bar {
  width: 90vw;
  height: 50px;
  /* background-color: white; */
  border-radius: 15px;
  margin-top: 16px;
  margin-bottom: 16px;
  display: flex;
  flex-direction: column;
  align-items: center;
}
/* .search-bar input {
  height: 90%;
  width: 80%;
  background-color: grey;
} */
.info-block,
.bottom-block {
  color: white;
  text-align: center;
  font-size: 1rem;
}
.location-name {
  font-weight: bold;
}

.big-temp-title {
  font-weight: bold;
  font-size: 0.7rem;
  margin-top: 16px;
  /* margin: 0; */
}
.big-temp {
  font-size: 3rem;
  font-weight: bold;
  line-height: 1;
}
.small-temp {
  font-weight: bold;
  font-size: 0.8rem;
  margin-bottom: 16px;
}
.avtar-block img {
  height: 368px;
}
.bottom-block {
  margin-top: 24px;
  width: 90vw;
  display: flex;
  align-items: center;
  justify-content: space-between;
}
.msg-block {
  width: 75vw;
  min-height: 60px;
  background-color: white;
  border-radius: 15px;
  color: #3d3d3d;
  text-align: left;
  word-wrap: break-word;
  padding: 8px 16px;
}
.feeling-btn {
  width: 50px;
  height: 50px;
  border-radius: 50%;
  background-color: #12a3c1;

    padding-top: 2px;
    font-size: 30px;
    font-weight: bold;

}
.feeling-inner-btn {
  height: 120px;
}

.feedback-thankyou-view {
  width: 100%;
  height: 100%;
  background-color: rgba(255,255,255,0.82);
  position: absolute !important;;
  top: 0;
  left: 0;
  display: flex;
  justify-content: center;
  align-items: center;

}
.feedback-thankyou-view > img {
  width: 80%;
}
</style>