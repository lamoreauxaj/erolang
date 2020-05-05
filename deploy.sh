#!/bin/bash

cd docs &&
npm install &&
pip install awscli --user &&
npm run build &&
aws s3 sync --acl public-read --sse --delete .vuepress/dist s3://erolang.xyz &&
cd .. &&
chmod 400 erolang.pem &&
ssh -i "erolang.pem" -o "StrictHostKeyChecking no" ubuntu@ec2-54-196-169-10.compute-1.amazonaws.com <<EOF
    cd pa &&
    rm -rf build &&
    rm -rf docs/node_modules &&
    git pull &&
    cd docs &&
    npm install &&
    cd .. &&
    mkdir build &&
    cd build &&
    cmake .. &&
    pm2 restart 0 &&
    exit
EOF