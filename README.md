# BlynkDoorLock
Control servo using NodeMCU chip via blynk.io

## Hardware
- NodeMCU 2.0
- TowerPro 995 servo motor
- Some wires
- Power bank 10,000 MAh with output 5V for NodeMCu

## IFTTT
- Create/configure a new applet
- First set Google assistance app and then choose webhook app for the applet
- Set anything that you want to command Google assistance
- Set this url in webhook GET request
```
    http://blynk-cloud.com/AUTH_TOKEN/update/V1?value=LOCK
```
- Follow blynk.io docs for more info
```
    https://blynkapi.docs.apiary.io/#
```