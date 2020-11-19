<template>
  <div class="hello">
    <div class="title-block">
      <h1>SD5509 Prototype</h1>
      <p>by Mandy, Shay & Hebitz</p>
    </div>

    <div class="data-container">
      <select name="location-select" id="location-select">
        <option>{{ deviceMeta.location.name }}</option>
      </select>
      <div class="temp-container">
        <p class="title">Current Temperature</p>
        <p class="temp">{{ temperature }} ℃</p>
      </div>
      <div class="hud-container">
        <p class="title">Humdity</p>
        <p class="hud">{{ humdity }} %</p>
      </div>
      <div class="update-container">
        <p class="title">Last update: {{ parsedTime }}</p>
      </div>
    </div>

    <div
      :id="map_id"
      style="height: 200px; width: 100%; position: absolute; bottom: 0"
    ></div>
  </div>
</template>

<script>
// import { createMapkit } from "vue-mapkit";
// import mapkit from "https://cdn.apple-mapkit.com/mk/5.x.x/mapkit.js";
import mapkit from "@solidsilver/mapkitjs";
import moment from "moment";
export default {
  name: "HelloWorld",
  props: {
    msg: String,
  },
  data() {
    return {
      data: null,
      temperature: 24.6,
      humdity: 60.0,
      topic: null,
      lastUpdate: 1605800321413,
      map: null,
      deviceMeta: {
        deviceId: "test_001_rpi3",
        location: {
          lat: 22.305585073619632,
          long: 114.17960954974454,
          name: "PolyU Innovation Tower, V1122",
        },
      },
    };
  },
  computed: {
    map_id() {
      return `map-${this._uid}`;
    },
    parsedTime() {
      return moment(this.lastUpdate).format();
    },
  },
  mounted() {
    mapkit.init({
      authorizationCallback: function (done) {
        // callback functionality goes here
        done(process.env.VUE_APP_MAPKIT_JWT);
      },
      language: "en",
    });
    this.map = new mapkit.Map(this.map_id);
    var MarkerAnnotation = mapkit.MarkerAnnotation;
    var sfo = new mapkit.Coordinate(
      this.deviceMeta.location.lat,
      this.deviceMeta.location.long
    );

    // var sfoRegion = new mapkit.CoordinateRegion(
    //   new mapkit.Coordinate(22.305585073619632, 114.17960954974454)
    //   new mapkit.CoordinateSpan(0.167647972, 0.354985255)
    // );
    var sfoAnnotation = new MarkerAnnotation(sfo, {
      color: this.temp2Hex(this.temperature),
      title: this.deviceMeta.location.name,
      glyphText: this.temp2Emoji(this.temperature),
    });
    this.map.showItems([sfoAnnotation]);

    // this.map.region = sfoRegion;
    return;
  },
  mqtt: {
    "sensor-update"(val) {
      let _msg = JSON.parse(val);
      this.data = _msg.res;
      this.temperature = _msg.res.temperature.toFixed(1);
      this.humdity = _msg.res.humidity.toFixed(1);
      this.lastUpdate = _msg.timestamp;
      this.deviceMeta = _msg.deviceMeta;
      console.table(_msg);
      // console.log(new TextDecoder("utf-8").decode(val));

      // this.buff = this.buff + data + '<br>'
    },
  },
  methods: {
    temp2Emoji: (temp) => {
      let _emoji = null;
      if (temp > 27) {
        _emoji = "🥵";
      } else if (temp < 19) {
        _emoji = "🥶";
      } else {
        _emoji = "😙";
      }
      return _emoji;
    },

    temp2Hex: (temp) => {
      let _hex = null;
      if (temp > 27) {
        _hex = "#e35d6a";
      } else if (temp < 19) {
        _hex = "#c6e2ff";
      } else {
        _hex = "#cbe330";
      }
      return _hex;
    },
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h1 {
  margin-bottom: 0;
  text-align: left;
}
.title-block > p {
  font-size: 0.8rem;
  font-weight: lighter;
  text-align: left;
  margin-top: 0;
}

.title-block {
  background-color: cornsilk;
  padding-left: 16px;
}
.hello {
  width: 100vw;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  /* margin: 0 16px;
  box-sizing: border-box; */
}
p {
  text-align: left;
}
.data-container {
  padding: 16px;
}

.data-container select {
  width: 100%;
}
.title {
  font-weight: bold;
  font-size: 0.8rem;
  margin-bottom: 0;
}
.temp {
  margin: 0;
  font-size: 6rem;
  font-weight: bold;
}
.hud,
.time {
  margin: 0;
  font-size: 4rem;
  font-weight: bold;
}

.map {
  width: 100%;
  height: 200px;
}
</style>
