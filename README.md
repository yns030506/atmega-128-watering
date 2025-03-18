# Project Title

---

토양 습도 센서를 이용한 식물 물주기 알람 시스템

### 주제 선정

---

 식물에 적절하게 물을 주는 것은 식물의 생존에 있어 필수적이다. 하지만 관리를 하다가 이를 잊어버리는 경우가 빈번히 발생할 수 있다. 따라서, 토양 습도 센서를 이용하여 실시간으로 토양 상태를 모니터링하고, 토양의 습도가 일정 이하로 떨어질 경우 경고음을 통해 물주기 알림을 제공하는 시스템을 구현하였다. 

### 구현 기능(진행 내용)

---

- 토양 습도 디스플레이

SZH-EK106 센서를 사용하여 토양의 실시간 습도 상태를 측정 후, LCD에 습도 상태를 디스플레이한다. 습도는 0에서 1024 사이 값으로 나타나고, 수분이 많을수록 값이 낮게 나온다. 

- 알람 기능

JKIT-128-1 키트에 내장되어 있는 buzzer를 이용하였으며, 토양 습도가 500 이하(기본 임계값)가 될 경우 알람음을 낸다.  스위치 2번을 누를 경우 60초간 알람 지연 기능을 사용할 수 있다. 2번 스위치를 누를 때마다 60초씩 추가지연되고, LCD에 지연된 시간이 초 단위로 디스플레이된다. 

- 임계값 설정 기능

스위치 1번을 통해 수분 알람 임계값을 재조정할 수 있다.  1번 스위치를 한 번 누를 때마다 임계값이 53씩 내려간다.  물에 담갔을 때의 센서값이 250 정도로 나오기 때문에, 임계값으로 설정할 수 있는 범위는 350에서 650 사이로 설정하였다.  값이 350일 때 1번 스위치를 누르면 650으로 값이 설정된다. 

### 데모 영상

---

https://youtube.com/shorts/isNel5jGqa8

### 주요 부품

---

- JKIT-128-1
    
    회로의 중심으로, 센서 데이터 처리, LCD 및 부저 제어의 역할을 한다. 
    
- LCD
    
    I2C 통신 방식을 사용하여 ATmega128 컨트롤러가 전송한 텍스트를 디스플레이한다. 
    
- SZH-EK106
    
    토양의 습도를 측정하는 센서 모듈로, 토양습도센서 프로브에 A/D 컨버터 모듈을 연결하여 사용한다. 
    

(부품 견적 내용)

| 상품코드  | 수량 | 상품명 | 단가 | 부가세 포함단가 | 금액 | 합계 |
|----------|------|------------------------------------------------------------------|------|------------|------|------|
| 1376532  | 1    | [SMG-A] 아두이노 토양 습도 센서 모듈 [SZH-EK106]               | 1,000 | 1,100      | 1,100 |      |
| 1327456  | 1    | [SMG] 아두이노 I2C 1602 LCD 모듈 [SZH-EK101]                   | 2,500 | 2,750      | 2,750 |      |
| 1321192  | 1    | [KEYES] 테스트[CH254] 소켓 점퍼 케이블 40P (칼라) (F/F) 20cm   |  850  |  935       |  935  |      |
|          |      |                                                                  |       |            |       | 4,785 |


---

### 회로도
![image](https://github.com/user-attachments/assets/0691cf6f-22c8-460a-9190-686e0044b41e)# atmega-128-watering

---

- LCD(I2C 통신 방식 사용) : PD0(SCL), PD1(SDA) 핀을 통해 Atmega128에서 LCD로 데이터를 전송한다.
- SZH-EK106 : 토양 습도 센서로, Atmega128이 센서가 보낸 아날로그 신호를 PE0핀으로 읽는다.
- Buzzer : JKIT-128-1 키트 내장 부품. PB4핀에 연결되어 있다.
- Switch : JKIT-128-1 키트 내장 부품. PE4, PE5 핀에 연결되어 있다.

---
- LCD 관련 모듈 : **Liquid Crystal I2C library for AVR 사용**

(https://github.com/denisgoriachev/liquid_crystal_i2c_avr)

- liquid_crystal_i2c.h
- liquid_crystal_i2c.c

(https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

- i2c_maseter.h
- i2c_maseter.c

### 결과 및 고찰

---

### 초기 구현 목표

본 프로젝트의 초기 목표는 다음 두 가지 기능을 구현하는 것이었다.

1. 경고음 알림 출력 기능
2. 실시간 습도를 LCD에 디스플레이하는 기능

이 두 기능은 모두 구현하는 데에 성공하였으며, 아래는 추가적으로 진행한 내용이다. 

### 추가된 기능 및 변경 사항, 개선사항

프로젝트를 진행하며 다음과 같은 추가적인 요구 사항과 개선점을 반영하였다.

1. **알림 임계값 설정 기능**
    - 흙 종류나 환경 상태에 따라 습도 환경이 달라질 수 있다는 점을 고려하여, 스위치를 통해 알림 임계값을 설정할 수 있는 기능을 추가하였다.
2. **알람 지연 기능**
    - 부저가 계속 울릴 경우 청각적인 부담을 줄이기 위해 알람 지연 기능을 추가하였다.
3. **멀티태스킹 개선**
    - 초기 구현에서는 부저가 울리는 동안 다른 기능을 사용할 수 없는 한계가 있었다. 이를 개선하기 위해 부저의 소리 간격을 줄이고, 소리와 소리 사이에 다른 작업이 수행될 수 있도록 구현하였다.
    - 그러나 인터럽트 방식을 활용하여 근본적으로 문제를 해결하려는 시도는 기한 내에 완료하지 못하였다. 향후 인터럽트 방식을 적용하여 소리가 나는 동안에도 다른 기능이 원활히 작동하도록 개선할 계획이다.
4. **사용자 입력 반영 개선**
    - 부저 소리가 나는 중간에도 스위치를 조작할 경우 설정이 즉시 반영되도록 개선이 필요하다.
5. **디스플레이 관련 변경 사항**
    - 알람 지연 시간은 FND에 디스플레이할 계획이었으나, 보유 중인 JKIT-128-1의 FND가 정상적으로 작동하지 않아 LCD에 모든 정보를 디스플레이하도록 변경하였다.
    - FND 문제를 해결하거나 대체 디스플레이 장치를 활용하는 방안을 검토 중이다.
