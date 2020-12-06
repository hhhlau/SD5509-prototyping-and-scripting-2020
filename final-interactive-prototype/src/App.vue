<template>
  <v-app>
    <v-main>
      <router-view></router-view>
    </v-main>
    <v-footer padless>
      <v-col class="text-center" cols="12">
        SD5509 - Protoyping & Scripting | Mandy, Shay, & Hebitz © 2020
      </v-col>
    </v-footer>
  </v-app>
</template>

<script>
export default {
  name: "App",

  components: {},

  data: () => ({
    //
  }),
};
</script>
