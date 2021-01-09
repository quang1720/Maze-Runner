// ý tưởng: khi xe đứng A.K.A cả hai cảm biến đo được giá trị thay đổi không quá 1,
long batdau;   // thời điểm khi cả 2 cảm biến không thay đổi giá trị quá 1
long thoigian; // thời gian giá trị cả 2 cảm biến có giá trị không thay đổi quá 1
static float temp1, temp2;
float ss, ss1;
void lui()
{
    //    static float temp1 = &cambientruoc, temp2 = &cambientrai;
    //    float ss, ss1;
    long batdau;   // thời điểm khi cả 2 cảm biến không thay đổi giá trị quá 1
    long thoigian; // thời gian giá trị cả 2 cảm biến có giá trị không thay đổi quá 1
    static float temp1, temp2;
    float ss, ss1;
    temp1 = cambientruoc, temp2 = cambientrai;
    analogWrite(ENB, 150);
    analogWrite(ENA, 150);
    ss = temp1 - cambientruoc;
    ss1 = temp2 - cambientruoc;
    if (ss1 <= 1 && ss <= 1)
    {
        batdau = millis();
        while (ss1 <= 1 && ss <= 1)
            ;
        long thoigian = millis() - batdau;
        Serial.print(thoigian);
    }
    if (thoigian == 2)
    {
        nghichphai();
        nghichtrai();
    }
}

void loop()
{
}