<template>
  <div class="home">
    <!-- <v-app-bar app color="red" dark>
      <div class="d-flex align-center">
        <v-img
          alt="Vuetify Logo"
          class="shrink mr-2"
          contain
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-logo-dark.png"
          transition="scale-transition"
          width="40"
        />

        <v-img
          alt="Vuetify Name"
          class="shrink mt-1 hidden-sm-and-down"
          contain
          min-width="100"
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-name-dark.png"
          width="100"
        />
      </div>

      <v-spacer></v-spacer>

      <v-btn
        href="https://github.com/vuetifyjs/vuetify/releases/latest"
        target="_blank"
        text
      >
        <span class="mr-2">Latest Release</span>
        <v-icon>mdi-open-in-new</v-icon>
      </v-btn>
    </v-app-bar> -->
    <!-- <HelloWorld msg="Welcome to Your Vue.js App" /> -->
    <div class="instruction-block ma-5">
      This page is designed for configuring the prototype to fit different cases for the user test session.
      <ul>
        <li>Adjusting weight is used for further customising the body temperature data based for user pre-test result</li>
      </ul>
    </div>
    <v-card class="mx-5 my-5">
      <v-card-title primary-title> User test setting </v-card-title>
      <v-card-text>
        <v-text-field
          name="name"
          label="Testing name"
          id="id"
          v-model="testProfile.name"
        ></v-text-field>
        <v-select
          :items="['Male', 'Female']"
          label="Gender"
          v-model="testProfile.gender"
        ></v-select>
        <v-select
          :items="['Natural', 'Fear cold', 'Fear hot']"
          label="Feeling tendance"
          v-model="testProfile.feelingTendance"
        ></v-select>
        <v-slider
            v-model="testProfile.weighting"
            class="align-center"
            max="5"
            min="-5"
            hide-details
            label="Adjusting weight"
          >
            <template v-slot:append>
              <v-text-field
                v-model="testProfile.weighting"
                class="mt-0 pt-0"
                hide-details
                single-line
                type="number"
                style="width: 60px"
              ></v-text-field>
            </template>
          </v-slider>
        <!-- <v-text-field
          name="weighting"
          type="number"
          label="Adjusting weight"
          max="5"
          min="-5"
          id="weight"
          v-model="testProfile.weighting"
        ></v-text-field> -->
        <v-select
          :items="[1, 2]"
          label="User test number"
          v-model="testProfile.testCaseNum"
        ></v-select>
      </v-card-text>
      <v-card-actions>
        <v-btn
          color="success"
          block
          :disabled="!isReadyToStart"
          @click="pushToTest"
          >Start the test</v-btn
        >
      </v-card-actions>
    </v-card>
  </div>
</template>

<script>
// @ is an alias to /src
// import HelloWorld from "@/components/HelloWorld.vue";

export default {
  name: "Home",
  computed: {
    isReadyToStart: function () {
      return (
        this.testProfile.name !== null &&
        this.testProfile.gender !== null &&
        this.testProfile.feelingTendance !== null &&
        this.testProfile.weighting !== null &&
        this.testProfile.testCaseNum !== null
      );
    },
  },
  data() {
    return {
      testProfile: {
        name: null,
        gender: null,
        feelingTendance: null,
        weighting: 0,
        testCaseNum: null,
      },
    };
  },
  methods: {
    pushToTest() {
      this.$router.push({
        name: "Test",
        params: {
          username: this.testProfile.name,
          gender: this.testProfile.gender,
          feelingTendance: this.testProfile.feelingTendance,
          weighting: parseInt(this.testProfile.weighting),
          testCase: this.testProfile.testCaseNum,
        },
      });
    },
  },
};
</script>

<style>
  .instruction-block {
    border-radius: 15px;
    background-color: #f0f0f0;
    padding: 16px;
    margin: 16px;
  }
</style>
