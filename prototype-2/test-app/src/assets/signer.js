"use strict";

const fs      = require("fs");
const jwt     = require("jsonwebtoken");

const privateKey = fs.readFileSync("AuthKey.p8").toString();
const teamId     = "3RQ45WH434";
const keyId      = "MBDXW255AA";

const header = {
    "alg": "ES256",
    "typ": "JWT",
    "kid": keyId
  }


const jwtToken = jwt.sign({
  "iss": teamId,
    "iat": Date.now() / 1000,
    "exp": (Date.now() / 1000) + 15778800,
}, privateKey, { header: header });

console.log(jwtToken);