# 1. WIFI Module - Lolin D1 Mini
[YouTube 링크](https://www.youtube.com/watch?v=nsmJlFtE8w4&list=PLJG0s98ECJWX3fJhhhsXWMIzIr00dd2tY&index=5 "Lolin 강의")
> ## Check Point 
- SSID에서 2.4GHz인지 확인하기 [5GHz는 지원하지 않음]
- PHY 모드, 채널의 GHz확인하기.



--------------------
> ## 코드 설명

```    
WiFi.begin("network-name", "pass-to-network");
```
- "network-name"    : WiFi ID

- "pass-to-network" : WiFi PWD

```
while(WiFi.status() != WL_CONNECTED);
```
- WiFi에 접속이 될때 까지 .을 찍는다는 뜻
  
```
WiFi.localIP();
```
- 접속된 와이파이의 주소를 띄워주는 명령어
---
<div style="page-break-after: always"></div>

# 2. WiFi 쉴드 종류
[YouTube 링크](https://www.youtube.com/watch?v=3BqdMjGL3kw&list=PLJG0s98ECJWX3fJhhhsXWMIzIr00dd2tY&index=5 "Lolin 쉴드")

- **Motor** : 모터 드라이버 
- **OLED**: 액정이 있는 모델
- **Barometric Pressure**: 기압, 온도 측정
- **TFT 2.4 touch**: 2.4인치 터치 스크린
- **Battery**: 프로버전의 리튬 건전지를 Mini에서 지원함
- **Dual, Tripler Base**: 횡방향 쉴드 보드
- **PIR**: PIR센서
- **Micro SD Card**: SD 카드
- **IR Controller**: 리모트 컨트롤 (적외선 송수신)
- **Ambient Light**: BH1750 조도 센서
- **DHT**: 온도, 습도 측정
- **Relay**: 외부 전자기기 On/Off 제어
- **Matrix LED**: 매트릭스 형태의 LED
- **Buzzer** : beep음을 냄
- **WS2812B RGB** : 네오픽셀이 1개
- **RGB LED** : 네오픽셀이 7개
- **ProtoBoard** : 다른 부품을 연결해서 보드 제작하고 싶을 때 사용
- **1 button** : 1 버튼 쉴드
- **DC Power** : DC잭을 연결해서 Power를 공급할 때 쓰임

[공식 Docs](https://www.wemos.cc/en/latest/d1_mini_shield/index.html "Wemos 쉴드 공식 Docs")

-----

<div style="page-break-after: always"></div>

# 3. PIN Numbering

[YouTube 링크](https://www.youtube.com/watch?v=1IoTI3q-owc&list=PLJG0s98ECJWX3fJhhhsXWMIzIr00dd2tY&index=6 "Lolin 쉴드")


> ### GPIO (General Purpose Input Output) = 다용도 입출력
- Arudino Uno의 Power, DIGITAL PWM, ANALOG IN의 핀들이 해당 됨.
- Arduino Uno에서 #PIN이 14를 넘어가게 되면, A0를 Digital Pin처럼 사용 가능하다.

```
ex) pinMode(14,OUTPUT); // A0의 pin을 Digital pin처럼 사용한다.
```

<center>
    <img src='Arduino_UNO_GPIO.png' alt='drawing' width=55% height=55%/>
</center>

----
> ## Wemos Lolin D1 mini v4.0 ESP8266 - GPIO 위치 
<br />

<center>
    <img src='Lolin_GPIO.png' alt='drawing' width=55% height=55%/>
</center>

- all of the IO pins run at 3.3V
- GPIO 대신 D0, D1 이런식으로도 설정 가능하다. (예제 마다 GPIO와 Pin번호가 다르게 사용 될 수 있다.)
```
ex) pinMode(D1, OUTPUT);
```