#include "touch.h"
#include "tim.h"


#define TPAD_ARR_MAX_VAL 0XFFFF//as the clock to do
vu16 tpad_default_val=0;				//���ص�ʱ��(û���ְ���),��������Ҫ��ʱ��


void TPAD_Reset(void){
	 GPIO_InitTypeDef GPIO_Initure;
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA5
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);	//PA5���0���ŵ�
    HAL_Delay(5);
    __HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_CC1|TIM_FLAG_UPDATE);   //�����־λ
    __HAL_TIM_SET_COUNTER(&htim2,0); //������ֵ��0
    
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      
    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
   // GPIO_Initure.Alternate=GPIO_AF1_TIM2;   //PA5����ΪTIM2ͨ��1
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	
	
	
}
u16  TPAD_Get_Val(void){
	   TPAD_Reset();
    while(__HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_CC1)==RESET) //�ȴ�����������
    {
        if(__HAL_TIM_GET_COUNTER(&htim2)>TPAD_ARR_MAX_VAL-500) return __HAL_TIM_GET_COUNTER(&htim2);//��ʱ�ˣ�ֱ�ӷ���CNT��ֵ
    };
    return HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);
	
}
u16 TPAD_Get_MaxVal(u8 n){
	
	u16 temp=0; 
	u16 res=0; 
	u8 lcntnum=n*2/3;//����2/3*n����Ч������,������Ч
	u8 okcnt=0;
	while(n--)
	{
		temp=TPAD_Get_Val();//�õ�һ��ֵ
		if(temp>(tpad_default_val*5/4))okcnt++;//���ٴ���Ĭ��ֵ��5/4������Ч
		if(temp>res)res=temp;
	}
	if(okcnt>=lcntnum)return res;//����2/3�ĸ���,Ҫ����Ĭ��ֵ��5/4������Ч
	else return 0;
	
}
u8  TPAD_Init(){
	u16 buf[10];
	u16 temp;
	u8 j,i;
	
	for(i=0;i<10;i++)//������ȡ10��
	{				 
		buf[i]=TPAD_Get_Val();
		HAL_Delay(10);	    
	}				    
	for(i=0;i<9;i++)//����
	{
		for(j=i+1;j<10;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	temp=0;
	for(i=2;i<8;i++)temp+=buf[i];//ȡ�м��8�����ݽ���ƽ��
	tpad_default_val=temp/6;
	if(tpad_default_val>(vu16)TPAD_ARR_MAX_VAL/2)return 1;//��ʼ����������TPAD_ARR_MAX_VAL/2����ֵ,������!
	return 0;
	
	
	
	
}
u8   TPAD_Scan(u8 mode){
	
	static u8 keyen=0;	//0,���Կ�ʼ���;>0,�����ܿ�ʼ���	 
	u8 res=0;
	u8 sample=3;	//Ĭ�ϲ�������Ϊ3��	 
	u16 rval;
	MX_TIM2_Init();
	if(mode)
	{
		sample=6;	//֧��������ʱ�����ò�������Ϊ6��
		keyen=0;	//֧������	  
	}
	rval=TPAD_Get_MaxVal(sample); 
	if(rval>(tpad_default_val*4/3)&&rval<(10*tpad_default_val))//����tpad_default_val+(1/3)*tpad_default_val,��С��10��tpad_default_val,����Ч
	{							 
		if(keyen==0)res=1;	//keyen==0,��Ч      	    					   
		keyen=3;				//����Ҫ�ٹ�3��֮����ܰ�����Ч   
	} 
	if(keyen)keyen--;		   							   		     	    					   
	return res;
	
}


//void TIM2_CH1_Cap_Init(u32 arr,u16 psc); 