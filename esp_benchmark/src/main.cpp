/**
 * Math Benchmark Test for MCU
 * Target: Arduino UNO/Mega, ESP32, STM32
 */

#include <Arduino.h> // PlatformIO에서는 이 줄이 필수입니다!
#include <math.h>

void setup() {
  // 통신 속도 설정 (platformio.ini의 monitor_speed와 맞춰야 함)
  Serial.begin(115200);
  
  // 시리얼 연결될 때까지 잠시 대기 (일부 보드 호환성 위해)
  while (!Serial) {
    delay(10);
  }

  Serial.println("\n\n==================================");
  Serial.println("   MCU Math Benchmark Started");
  Serial.println("==================================");

  // 보드 정보 출력 (컴파일 타임 매크로 확인)
  Serial.print("Target Board: ");
  #if defined(ESP32)
    Serial.println("ESP32 (32-bit)");
  #elif defined(ARDUINO_AVR_MEGA2560)
    Serial.println("Arduino Mega 2560 (8-bit)");
  #elif defined(ARDUINO_AVR_UNO)
    Serial.println("Arduino UNO (8-bit)");
  #elif defined(ARDUINO_ARCH_STM32)
    Serial.println("STM32 (32-bit)");
  #else
    Serial.println("Unknown Board");
  #endif

  // --- 벤치마크 설정 ---
  long iterations = 100000; // 10만 번 반복
  float result = 0;
  
  Serial.print("Iterations: "); 
  Serial.println(iterations);
  Serial.println("Calculating... please wait.");

  // --- 측정 시작 ---
  unsigned long startTime = micros(); // 시작 시간 기록

  for (long i = 0; i < iterations; i++) {
    // 0.01씩 증가하는 각도에 대해 sin + cos 연산 수행
    float angle = i * 0.01;
    result += sin(angle) + cos(angle);
  }

  unsigned long endTime = micros();   // 종료 시간 기록
  // --- 측정 종료 ---

  unsigned long duration = endTime - startTime;

  // 결과 출력
  Serial.println("\n----------------------------------");
  Serial.print("Total Time: "); 
  Serial.print(duration); 
  Serial.println(" us (microseconds)");
  
  Serial.print("Total Time: "); 
  Serial.print(duration / 1000.0, 3); 
  Serial.println(" ms (milliseconds)");
  Serial.println("----------------------------------");
  
  // 컴파일러가 계산 코드를 '쓸모없다'고 판단해서 삭제하는 것을 방지하기 위해 결과값 출력
  Serial.print("Calculation Checksum: "); 
  Serial.println(result);
}

void loop() {
  // 벤치마크는 한 번만 실행하고 종료
  delay(1000);
}