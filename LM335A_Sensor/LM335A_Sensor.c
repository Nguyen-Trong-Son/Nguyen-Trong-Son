#include "LM335A_Sensor.h"
#include "stdlib.h"

// protype
static void LM335A_ADC_Config(LM335A_HandleTypeDef *Lm335a_x);

/**
 * @brief LM335A_ADC_Config
 * 
 * @param Lm335a_x 
 */
static void LM335A_ADC_Config(LM335A_HandleTypeDef *Lm335a_x)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_11;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
    if (HAL_ADC_ConfigChannel(Lm335a_x->ADC_LM335A, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief LM335A_Init
 * 
 * @param Lm335a_x 
 * @param adc 
 * @param Lm335a_Chanel_ADC 
 * @param Lm335a_Rank_ADC 
 * @param Lm335a_Sample_Time 
 */
void LM335A_Init(LM335A_HandleTypeDef *Lm335a_x,ADC_HandleTypeDef *adc)
{
    Lm335a_x->ADC_LM335A = adc;
}


/**
 * @brief LM335A_Measuring
 * 
 * @param Lm335a_x 
 * @param sample 
 * @return float 
 */
float LM335A_Measuring(LM335A_HandleTypeDef *Lm335a_x, uint8_t sample)
{
    uint32_t sum = 0, data = 0;
    uint16_t arr_adc_value[sample];
    uint8_t index = 0;
    float calcVoltage = 0;
    float Temperature = 0;

    for(uint8_t i = 0; i < sample; i++)
    {
        LM335A_ADC_Config(Lm335a_x);
        HAL_ADC_Start(Lm335a_x->ADC_LM335A);
        HAL_ADC_PollForConversion(Lm335a_x->ADC_LM335A,1000);
        arr_adc_value[i] = HAL_ADC_GetValue(Lm335a_x->ADC_LM335A);
        HAL_ADC_Stop(Lm335a_x->ADC_LM335A);
        HAL_Delay(100);
    }

    for(uint8_t i = 0; i < sample; i++)
    {
        sum += arr_adc_value[i];
    }

    data  = sum / sample;
    index = sample;

    for(uint8_t i = 0; i < sample; i++)
    {
        if(abs(data - arr_adc_value[i]) > data)
        {
            arr_adc_value[i] = 0;
            index --;
        }
    }

    sum = 0;
    data = 0;

    for (uint8_t i = 0; i < sample; i++)
    {
        sum += arr_adc_value[i];
    }

    data = sum / index;
    //data += 77;


    calcVoltage = (float)(((float)data / 4095.0f) *3.3f);

    Temperature = calcVoltage * 10;

    return Temperature;
}
