<template>
  <div class="prototype-view">
      <div class="search-bar">
          <input type="text">
      </div>
      <div class="info-block">
          <div class="location-name">
              fndsgdsfnvldnfgiv
          </div>
          <div class="data-point-from-time">lkjsdkjlsdjkf</div>
          <div class="big-temp">20℃</div>
          <div class="small-temp">15</div>
      </div>
      <div class="avtar-block">
          <img :src="require('@/assets/boy-cold.png')" alt="">
      </div>
      <div class="bottom-block">
          <div class="msg-block">zjkhvbsxvjsdbjvsadvksajdvkjsdbvkjbsadkjvbaksjdvbkjsadblkjcbsadljkvbskdjvbkjsadbvlkjbsadkjvbkjsdlbvljsabdjvbaskd</div>
          <div class="feeling-btn"></div>
      </div>

  </div>
</template>

<script>
export default {
    name: "ProtypeView"
}
</script>

<style>
    .prototype-view {
        width: 100vw;
        height: 100vh;
        background-color: black;
        display: flex;
        flex-direction: column;
        align-items: center;
    }
    .search-bar {
        width: 90vw;
        height: 50px;
        background-color:white;
        border-radius: 15px;
        margin-top: 16px;
        margin-bottom: 16px;
        display: flex;
        flex-direction: column;
        align-items: center;



    }
    .search-bar input {
        height: 90%;
        width: 80%;
        background-color: grey;
    }
    .info-block, .bottom-block {
        color: white;
        text-align: center;
        font-size: 1rem;
    }
    .location-name {
        font-weight: bold;
    }
    .big-temp {
        font-size:3rem;
        font-weight: bold;
    }
    .small-temp {
        font-weight: bold;
        font-size: 0.8rem;
    }
    .avtar-block img {
        height: 368px;
    }
    .bottom-block {
        margin-top: 24px;
        width:90vw;
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
        text-align:left;
        word-wrap: break-word;
        padding: 8px 16px;   
    }
    .feeling-btn {
        width: 50px;
        height: 50px;
        border-radius: 50%;background-color: #12a3c1;
    }
</style>