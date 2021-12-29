#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>
#include <stdbool.h>

#define QUT 50               // 서보모터 정방향 회전 값
#define RQUT 51              // 서보모터 반대방향 회전 값

#define TRIG 23              // HC-SR04 Trig 핀
#define ECHO 24              // HC-SR04 Echo 핀

#define SERVO 26             // SG90 데이터 핀

#define ROWS 4               // Keypad Rows 값
#define COLS 4               // Keypad Cols 값

int rowPins[ROWS] = { 1, 4, 5, 6 };      // Keypad Rows 핀
int colPins[COLS] = { 12, 3, 2, 0 };     // Keypad Cols 핀

char pw[5] = { '1', '2', '3', '4' };     // 비밀번호 

char keys[ROWS][COLS] = {               // 키패드에 배정되는 값
   {'1', '2', '3', 'A'},
   {'4', '5', '6', 'B'},
   {'7', '8', '9', 'C'},
   {'*', '0', '#', 'D'}
};

bool Q_Flag = false;

void Setup()                         // pinMode 설정 함수
{
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    for (int c = 0; c < COLS; c++)
    {
        pinMode(colPins[c], OUTPUT);
        digitalWrite(colPins[c], HIGH);
    }

    for (int r = 0; r < ROWS; r++)
    {
        pinMode(rowPins[0], INPUT);
        pullUpDnControl(rowPins[r], PUD_UP);
    }
}

float Ultra()                   // 초음파 값 설정 함수
{
    int start_time, end_time = 0;
    float distance;

    digitalWrite(TRIG, LOW);
    delay(500);

    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG, LOW);

    while (digitalRead(ECHO) == 0);
    start_time = micros();

    while (digitalRead(ECHO) == 1);
    end_time = micros();

    distance = (end_time - start_time) / 29. / 2.;

    return distance;
}

void Servo(int q)               // 서보모터 동작 함수
{
    softPwmCreate(SERVO, 0, 200);

    if (q == QUT)
    {
        printf("Lock\n");

        Q_Flag = true;
        softPwmWrite(SERVO, 18);
        delay(600);
    }

    else if (q == RQUT)
    {
        printf("unLock\n");

        Q_Flag = false;
        softPwmWrite(SERVO, 5);
        delay(600);
    }
}

int findLowRow()                      // Keypad의 rowPin 값 찾기
{
    for (int r = 0; r < ROWS; r++)
    {
        if (digitalRead(rowPins[r]) == LOW)
            return r;
    }

    return -1;
}

char Keypad()                         // Keypad 동작 함수
{
    int rowIndex;
    char pressedKey = '\0';

    for (int c = 0; c < COLS; c++)
    {
        digitalWrite(colPins[c], LOW);

        rowIndex = findLowRow();

        if (rowIndex > -1)
        {
            if (!pressedKey)
                pressedKey = keys[rowIndex][c];

            return pressedKey;
        }

        digitalWrite(colPins[c], HIGH);
    }

    return pressedKey;
}

void Check()                       // 비밀번호 체크 함수
{
    char My_pw[5];
    char temp = '\0';

    int i = 0;
    int cnt = 0;

    while (1)
    {
        while (1)
        {
            temp = Keypad();
            if (temp)
            {
                if (temp == '*')
                {
                    break;
                }

                else
                {
                    My_pw[i] = temp;
                    printf("insert %c\n", My_pw[i]);
                    i += 1;
                }
            }
            delay(250);
        }

        i = 0;
        temp = '\0';

        for (int k = 0; k < 4; k++)
        {
            if (pw[k] == My_pw[k])
            {
                cnt += 1;
            }
        }

        if (cnt == 4)
        {
            printf("success\n");
            cnt = 0;

            Servo(RQUT);
            delay(5000);

            goto EXIT;
        }

        else
        {
            printf("Error!\n");
            cnt = 0;

            for (int u = 0; u < 5; u++)
            {
                My_pw[u] = '\0';
            }
            delay(250);
        }
    }

EXIT:
    for (int j = 0; j < 5; j++)
    {
        My_pw[j] = '\0';
    }

    delay(250);
}

int main(void)
{
    if (wiringPiSetup() < 0) {
        exit(0);
    }

    Setup();

    float dist = 0;
    char ch;

    printf("start\n");

    while (1)
    {
        dist = Ultra();
        if (dist < 10.0 && Q_Flag == false)
        {
            delay(3000);
            Servo(QUT);
        }

        ch = Keypad();
        if (ch)
        {
            if (ch == '#')           // 비밀번호 체크로 이동
            {
                printf("press : %c\n", ch);
                delay(250);
                Check();
            }
        }
        delay(250);
    }
}