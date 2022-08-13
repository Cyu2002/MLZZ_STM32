#include "touch.h"
#include "tim.h"


#define TPAD_ARR_MAX_VAL 0XFFFF//as the clock to do
vu16 tpad_default_val=0;				//空载的时候(没有手按下),计数器需要的时间


void TPAD_Reset(void){
	 GPIO_InitTypeDef GPIO_Initure;
	
    GPIO_Initure.Pin=GPIO_PIN_0;            //PA5
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);	//PA5输出0，放电
    HAL_Delay(5);
    __HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_CC1|TIM_FLAG_UPDATE);   //清除标志位
    __HAL_TIM_SET_COUNTER(&htim2,0); //计数器值归0
    
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉
   // GPIO_Initure.Alternate=GPIO_AF1_TIM2;   //PA5复用为TIM2通道1
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	
	
	
}
u16  TPAD_Get_Val(void){
	   TPAD_Reset();
    while(__HAL_TIM_GET_FLAG(&htim2,TIM_FLAG_CC1)==RESET) //等待捕获上升沿
    {
        if(__HAL_TIM_GET_COUNTER(&htim2)>TPAD_ARR_MAX_VAL-500) return __HAL_TIM_GET_COUNTER(&htim2);//超时了，直接返回CNT的值
    };
    return HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);
	
}
u16 TPAD_Get_MaxVal(u8 n){
	
	u16 temp=0; 
	u16 res=0; 
	u8 lcntnum=n*2/3;//至少2/3*n的有效个触摸,才算有效
	u8 okcnt=0;
	while(n--)
	{
		temp=TPAD_Get_Val();//得到一次值
		if(temp>(tpad_default_val*5/4))okcnt++;//至少大于默认值的5/4才算有效
		if(temp>res)res=temp;
	}
	if(okcnt>=lcntnum)return res;//至少2/3的概率,要大于默认值的5/4才算有效
	else return 0;
	
}
u8  TPAD_Init(){
	u16 buf[10];
	u16 temp;
	u8 j,i;
	
	for(i=0;i<10;i++)//连续读取10次
	{				 
		buf[i]=TPAD_Get_Val();
		HAL_Delay(10);	    
	}				    
	for(i=0;i<9;i++)//排序
	{
		for(j=i+1;j<10;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}
	temp=0;
	for(i=2;i<8;i++)temp+=buf[i];//取中间的8个数据进行平均
	tpad_default_val=temp/6;
	if(tpad_default_val>(vu16)TPAD_ARR_MAX_VAL/2)return 1;//初始化遇到超过TPAD_ARR_MAX_VAL/2的数值,不正常!
	return 0;
	
	
	
	
}
u8   TPAD_Scan(u8 mode){
	
	static u8 keyen=0;	//0,可以开始检测;>0,还不能开始检测	 
	u8 res=0;
	u8 sample=3;	//默认采样次数为3次	 
	u16 rval;
	MX_TIM2_Init();
	if(mode)
	{
		sample=6;	//支持连按的时候，设置采样次数为6次
		keyen=0;	//支持连按	  
	}
	rval=TPAD_Get_MaxVal(sample); 
	if(rval>(tpad_default_val*4/3)&&rval<(10*tpad_default_val))//大于tpad_default_val+(1/3)*tpad_default_val,且小于10倍tpad_default_val,则有效
	{							 
		if(keyen==0)res=1;	//keyen==0,有效      	    					   
		keyen=3;				//至少要再过3次之后才能按键有效   
	} 
	if(keyen)keyen--;		   							   		     	    					   
	return res;
	
}


//void TIM2_CH1_Cap_Init(u32 arr,u16 psc); 