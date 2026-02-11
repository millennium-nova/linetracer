// センサーのピン設定
const int analogIN0 = A0; // アナログ入力0のピン
const int D0 = 7;         // デジタル入力0のピン
const int analogIN1 = A1; // アナログ入力1のピン
const int D1 = 6;         // デジタル入力1のピン

// モータードライバのピン設定
const int E1 = 5; // モーター1の速度制御ピン
const int M1 = 4; // モーター1の方向制御ピン
const int E2 = 3; // モーター2の速度制御ピン
const int M2 = 2; // モーター2の方向制御ピン

// 制御に使用する定数
const int THRESHOLD = 450;      // センサーの閾値
const int SPEED_INNER = 35;     // カーブ内側のモーター速度
const int SPEED_OUTER = 255;    // カーブ外側のモーター速度
const int SPEED_LINEAR = 210;   // 直線走行時のモーター速度

void setup() {
    // モータードライバピンを出力に設定
    pinMode(M1, OUTPUT);  
    pinMode(M2, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
}

void controlMotors(int speedLeft, int speedRight) {
    // モーター制御関数
    // 指定された速度で左右のモーターを制御
    digitalWrite(M1, LOW); // 方向は常に同じ（LOW）
    digitalWrite(M2, LOW);     
    analogWrite(E1, speedLeft);   // 左モーターの速度設定
    analogWrite(E2, speedRight);  // 右モーターの速度設定
}

void loop() {
    // センサーからの値を読み取る
    int Aval0 = analogRead(analogIN0);
    int Dval0 = digitalRead(D0);
    int Aval1 = analogRead(analogIN1);
    int Dval1 = digitalRead(D1);

    // センサー値に基づいてモーターを制御
    if ((Dval0 == 0 && Dval1 == 0) || (Dval0 == 1 && Dval1 == 1)) {
        // 両方のデジタルセンサーが同じ値の場合の処理
        if (Aval0 > THRESHOLD && Aval1 <= THRESHOLD) {
        // 左センサーが閾値以上で右センサーが閾値以下の場合
        controlMotors(SPEED_INNER, SPEED_OUTER);
        } else if (Aval0 <= THRESHOLD && Aval1 > THRESHOLD) {
        // 右センサーが閾値以上で左センサーが閾値以下の場合
        controlMotors(SPEED_OUTER, SPEED_INNER);
        } else {
        // それ以外（両方のセンサーが閾値以上または以下の場合）
        controlMotors(SPEED_LINEAR, SPEED_LINEAR);
        }
    } else if (Dval0 == 1 && Dval1 == 0) {
        // 左センサーが1で右センサーが0の場合
        controlMotors(SPEED_INNER, SPEED_OUTER);
    } else {
        // その他（右センサーが1で左センサーが0）の場合
        controlMotors(SPEED_OUTER, SPEED_INNER);
    }
}
  