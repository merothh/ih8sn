#!/bin/bash

adb wait-for-device root
adb wait-for-device remount
adb wait-for-device push etc/60-ih8sn.sh /system/addon.d/
adb wait-for-device push ih8sn /system/bin/
adb wait-for-device push etc/ih8sn.rc /system/etc/init/

SERIALNO=$(adb shell getprop ro.boot.serialno)
PRODUCT=$(adb shell getprop ro.build.product)

if [[ -f "etc/ih8sn.conf.${SERIALNO}" ]]; then
    adb wait-for-device push etc/ih8sn.conf.${SERIALNO} /system/etc/ih8sn.conf
elif [[ -f "etc/ih8sn.conf.${PRODUCT}" ]]; then
    adb wait-for-device push etc/ih8sn.conf.${PRODUCT} /system/etc/ih8sn.conf
else
    adb wait-for-device push etc/ih8sn.conf /system/etc/
fi
