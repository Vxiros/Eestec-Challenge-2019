#!/bin/bash

cd unknown
rm -rf
streamer -f jpeg -o unknown.jpeg
cd ../
face_recognition ./known ./unknown/ | cut -d ',' -f2
