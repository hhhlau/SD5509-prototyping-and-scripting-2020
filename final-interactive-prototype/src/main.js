import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import vuetify from "./plugins/vuetify";
import VueMqtt from 'vue-mqtt';

Vue.config.productionTip = false;
Vue.use(VueMqtt, 'mqtt://b9155527:881fabd58c0f4d8e@broker.shiftr.io', {"clientId": "app-client"});


new Vue({
  router,
  vuetify,
  render: h => h(App)
}).$mount("#app");
