/**
 * @file Display_LCD_Parameter.c
 * @author Nguyen Trong Son (LoH Technology Company Limited)
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Display_LCD_Parameter.h"
#include "stdio.h"
#include "string.h"


/**
 * @brief Display_Setup_Parameter_Pm2_5
 * 
 * @param LCD 
 * @param pm2_5 
 * @param satatic_data_pm2_5 
 */
void Display_Setup_Parameter_Pm2_5(CLCD_I2C_Name *LCD, uint16_t satatic_data_pm2_5)
{
    char string1[10];
    sprintf(string1, "%d", satatic_data_pm2_5);
    CLCD_I2C_SetCursor(LCD, 0,0);
    CLCD_I2C_WriteString(LCD, "Pm2_5_(ug/m3)");
//    CLCD_I2C_SetCursor(LCD, 0, 1);
//    CLCD_I2C_WriteString(LCD, "SetupCalib:     ");
//    CLCD_I2C_SetCursor(LCD, 1,1);
//    CLCD_I2C_WriteString(LCD, string1);

    // /*range 0 - 99 ug/m3*/
     if( (0 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 99))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 100 - 200 ug/m3*/
     if( (100 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 200))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1,1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4,1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 200 - 300 ug/m3*/
     if( (200 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 300))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 300 - 400 ug/m3*/
     if( (300 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 400))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 400 - 500 ug/m3*/
     if((400 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 500))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 500 - 600 ug/m3*/
     if((500 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 600))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 600 - 700 ug/m3*/
     if((600 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 700))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 700 - 800 ug/m3*/
     if((700 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 800))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 800 - 900 ug/m3*/
     if((800 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 900))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 900 - 1000 ug/m3*/
     if((900 <= satatic_data_pm2_5) && (satatic_data_pm2_5 <= 999))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 900 - 1000 ug/m3*/
     if(satatic_data_pm2_5 == 1000)
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);

     }

}

/**
 * @brief Display_Setup_Parameter_Sum_pm
 * 
 * @param LCD 
 * @param sum_pm 
 * @param satatic_data_sum_pm 
 */
void Display_Setup_Parameter_Sum_pm(CLCD_I2C_Name *LCD, uint16_t satatic_data_sum_pm)
{
    char string1[10];
    sprintf(string1, "%d", satatic_data_sum_pm);

    CLCD_I2C_SetCursor(LCD, 0,0);
    CLCD_I2C_WriteString(LCD, "SumPm_(ug/m3)");
//    CLCD_I2C_SetCursor(LCD, 0, 1);
//    CLCD_I2C_WriteString(LCD, "SetupCalib:    ");
//    CLCD_I2C_SetCursor(LCD, 11, 1);
//    CLCD_I2C_WriteString(LCD, string1);


     /*range 0 - 99 ug/m3*/
     if(( 0 <= satatic_data_sum_pm) && (satatic_data_sum_pm <= 99))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1,1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3,1);
         CLCD_I2C_WriteChar(LCD, ' ');
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4,1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 100 - 200 ug/m3*/
     if((100 <= satatic_data_sum_pm) && (satatic_data_sum_pm <= 200))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1,1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 200 - 300 ug/m3*/
     if((200 <= satatic_data_sum_pm) && (satatic_data_sum_pm <= 300))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 300 - 400 ug/m3*/
     if((300 <= satatic_data_sum_pm) && (satatic_data_sum_pm <= 400))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 400 - 500 ug/m3*/
     if((400 <= satatic_data_sum_pm) && (satatic_data_sum_pm <= 500))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }
}

/**
 * @brief Display_Setup_Parameter_Co2
 * 
 * @param LCD 
 * @param co2_ppm 
 * @param satatic_data_pm2_5 
 */
void Display_Setup_Parameter_Co2(CLCD_I2C_Name *LCD, uint16_t satatic_data_co2)
{
    char string1[10];
    sprintf(string1, "%d", satatic_data_co2);
    CLCD_I2C_SetCursor(LCD, 0,0);
    CLCD_I2C_WriteString(LCD, "Co2_(ppm)");
//    CLCD_I2C_SetCursor(LCD, 0, 1);
//    CLCD_I2C_WriteString(LCD, "SetupCalib:     ");
//    CLCD_I2C_SetCursor(LCD, 1, 1);
//    CLCD_I2C_WriteString(LCD, string1);

     /*range 0 - 99 ppm*/
     if(( 0 <= satatic_data_co2) && (satatic_data_co2 <= 99))
     {

         CLCD_I2C_SetCursor(LCD, 0, 1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3,1);
         CLCD_I2C_WriteChar(LCD, ' ');
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 100 - 200 ppm*/
     if((100 <= satatic_data_co2) && (satatic_data_co2 <= 200))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 200 - 300 ppm*/
     if((200 <= satatic_data_co2) && (satatic_data_co2 <= 300))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 300 - 400 ppm*/
     if((300 <= satatic_data_co2) && (satatic_data_co2 <= 400))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 400 - 500 ppm*/
     if((400 <= satatic_data_co2) && (satatic_data_co2 <= 500))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 500 - 600 ppm*/
     if((500 <= satatic_data_co2) && (satatic_data_co2 <= 600))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 600 - 700 ppm*/
     if((600 <= satatic_data_co2) && (satatic_data_co2 <= 700))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 700 - 800 ppm*/
     if((700 <= satatic_data_co2) && (satatic_data_co2 <= 800))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 800 - 900 ppm*/
     if((800 <= satatic_data_co2) && (satatic_data_co2 <= 900))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 900 - 1000 ppm*/
     if((900 <= satatic_data_co2) && (satatic_data_co2 <= 999))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4,1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     if(satatic_data_co2 == 1000)
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
     }

}


/**
 * @brief Display_Setup_Parameter_So2
 * 
 * @param LCD 
 * @param so2_ppm 
 * @param satatic_data_so2 
 */
void Display_Setup_Parameter_So2(CLCD_I2C_Name *LCD, uint16_t satatic_data_so2)
{
    char string1[10];
    sprintf(string1, "%d", satatic_data_so2);
    CLCD_I2C_SetCursor(LCD, 0,0);
    CLCD_I2C_WriteString(LCD, "So2_(ppm)");
//    CLCD_I2C_SetCursor(LCD, 0,1);
//    CLCD_I2C_WriteString(LCD, "SetupCalib:     ");
//    CLCD_I2C_SetCursor(LCD, 1,1);
//    CLCD_I2C_WriteString(LCD, string1);

     /*range 0 - 99 ppm*/
     if(( 0 <= satatic_data_so2) && (satatic_data_so2 <= 99))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 100 - 200 ppm*/
     if((100 <= satatic_data_so2) && (satatic_data_so2 <= 200))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 200 - 300 ppm*/
     if((200 <= satatic_data_so2) && (satatic_data_so2 <= 300))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 300 - 400 ppm*/
     if((300 <= satatic_data_so2) && (satatic_data_so2 <= 400))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 400 - 500 ppm*/
     if((400 <= satatic_data_so2) && (satatic_data_so2 <= 500))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 500 - 600 ppm*/
     if((500 <= satatic_data_so2) && (satatic_data_so2 <= 600))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 600 - 700 ppm*/
     if((600 <= satatic_data_so2) && (satatic_data_so2 <= 700))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 700 - 800 ppm*/
     if((700 <= satatic_data_so2) && (satatic_data_so2 <= 800))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 800 - 900 ppm*/
     if((800 <= satatic_data_so2) && (satatic_data_so2 <= 900))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 900 - 1000 ppm*/
     if((900 <= satatic_data_so2) && (satatic_data_so2 <= 999))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 4, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }


     /*range 900 - 1000 ppm*/
     if(satatic_data_so2 == 1000)
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);

     }
}


/**
 * @brief Display_Setup_Parameter_Humidity
 * 
 * @param LCD 
 * @param humidity 
 * @param satatic_data_humididy 
 */
void Display_Setup_Parameter_Humidity(CLCD_I2C_Name *LCD, uint8_t satatic_data_humididy)
{
    char string1[10];
    sprintf(string1, "%d", satatic_data_humididy);

    CLCD_I2C_SetCursor(LCD, 0,0);
    CLCD_I2C_WriteString(LCD, "Humidity_(");
    CLCD_I2C_WriteChar(LCD, '%');
    CLCD_I2C_WriteChar(LCD, ')');
//    CLCD_I2C_SetCursor(LCD, 0,1);
//    CLCD_I2C_WriteString(LCD, "SetupCalib:     ");
//    CLCD_I2C_SetCursor(LCD, 1,1);
//    CLCD_I2C_WriteString(LCD, string1);

     /*range 0 - 9 %*/
     if(( 0 <= satatic_data_humididy) && (satatic_data_humididy <= 9))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 2, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 10 - 20 % */
     if((10 <= satatic_data_humididy) && (satatic_data_humididy <= 20))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 20 - 30 % */
     if((20 <= satatic_data_humididy) && (satatic_data_humididy <= 30))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');

     }

     /*range 30 - 40 % */
     if((30 <= satatic_data_humididy) && (satatic_data_humididy <= 40))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 40 - 50 % */
     if((40 <= satatic_data_humididy) && (satatic_data_humididy <= 50))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 50 - 60 % */
     if((50 <= satatic_data_humididy) && (satatic_data_humididy <= 60))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 60 - 70 % */
     if((60 <= satatic_data_humididy) && (satatic_data_humididy <= 70))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 70 - 80 % */
     if((70 <= satatic_data_humididy) && (satatic_data_humididy <= 80))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 80 - 90 % */
     if((80 <= satatic_data_humididy) && (satatic_data_humididy <= 90))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 90 - 100 ppm*/
     if((90 <= satatic_data_humididy) && (satatic_data_humididy <= 99))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     if(satatic_data_humididy == 100)
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
     }
}


/**
 * @brief Display_Setup_Parameter_Temperature
 * 
 * @param LCD 
 * @param temperature 
 * @param satatic_data_temperature 
 */
void Display_Setup_Parameter_Temperature(CLCD_I2C_Name *LCD, uint8_t satatic_data_temperature)
{
    char string1[10];
    sprintf(string1, "%.1d", satatic_data_temperature);
    CLCD_I2C_SetCursor(LCD, 0,0);
    CLCD_I2C_WriteString(LCD, "Temperature ");
    CLCD_I2C_WriteChar(LCD, 0xDF);
    CLCD_I2C_WriteChar(LCD, 'C');
//    CLCD_I2C_SetCursor(LCD, 0,1);
//    CLCD_I2C_WriteString(LCD, "SetupCalib:     ");
//    CLCD_I2C_SetCursor(LCD, 1,1);
//    CLCD_I2C_WriteString(LCD, string1);
    
     /*range 0 - 9 °C*/
     if(( 0 <= satatic_data_temperature) && (satatic_data_temperature <= 9))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 2, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 10 - 20 °C */
     if((10 <= satatic_data_temperature) && (satatic_data_temperature <= 20))
     {
         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 20 - 30 °C */
     if((20 <= satatic_data_temperature) && (satatic_data_temperature <= 30))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');

     }

     /*range 30 - 40 °C */
     if((30 <= satatic_data_temperature) && (satatic_data_temperature <= 40))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');

     }

     /*range 40 - 50 % */
     if((40 <= satatic_data_temperature) && (satatic_data_temperature <= 50))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }

     /*range 50 - 60 °C */
     if((50 <= satatic_data_temperature) && (satatic_data_temperature <= 60))
     {

         CLCD_I2C_SetCursor(LCD, 0,1);
         CLCD_I2C_WriteString(LCD, "SetupCalib:");
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 1, 1);
         CLCD_I2C_WriteString(LCD, string1);
         CLCD_I2C_SetCursor(LCD, strlen("SetupCalib:") + 3, 1);
         CLCD_I2C_WriteChar(LCD, ' ');
     }
}

/**
 * @brief Display_Done
 * 
 * @param LCD 
 */
void Display_Done(CLCD_I2C_Name *LCD, float value)
{
	char string1[10];
	sprintf(string1, "%.1f", value);


    /*range 0 - 99 ppm*/
    if(( 0 <= value) && (value <= 9))
    {

        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "D_Value:");
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 4, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 5, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 6, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
    }


    /*range 0 - 99 ppm*/
    if(( 10 <= value) && (value <= 99))
    {

        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "D_Value:");
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 5, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 6, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
    }

    /*range 900 - 1000 ppm*/
    if((100 <= value) && (value <= 999))
    {
        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "D_Value:");
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 6, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
    }

    if(value == 1000)
    {
        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "D_Value:");
        CLCD_I2C_SetCursor(LCD, strlen("D_Value:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);

    }

}


void Display_Monitor(CLCD_I2C_Name *LCD, float value)
{
	char string1[10];
	sprintf(string1, "%.1f", value);


    /*range 0 - 99 ppm*/
    if(( 0 <= value) && (value <= 9))
    {

        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "Output:");
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 4, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 5, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 6, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
    }


    /*range 0 - 99 ppm*/
    if(( 10 <= value) && (value <= 99))
    {

        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "Output:");
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 5, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 6, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
    }

    /*range 900 - 1000 ppm*/
    if((100 <= value) && (value <= 999))
    {
        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "Output:");
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 6, 2);
        CLCD_I2C_WriteChar(LCD, ' ');
    }

    if(value == 1000)
    {
        CLCD_I2C_SetCursor(LCD, 0,2);
        CLCD_I2C_WriteString(LCD, "Output:");
        CLCD_I2C_SetCursor(LCD, strlen("Output:") + 0, 2);
        CLCD_I2C_WriteString(LCD, string1);

    }
}

