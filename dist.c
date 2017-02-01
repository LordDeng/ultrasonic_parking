#include <16F886.h>
#FUSES INTRC_IO,INTRC,NOWDT,NOPROTECT,PUT,NOBROWNOUT,NOLVP,NOMCLR  
#use delay(clock=4000000)
#USE standard_io(a,b,c,e)
#define LCD_ENABLE_PIN PIN_A3
#define LCD_RS_PIN PIN_A2
#define LCD_RW_PIN PIN_A1
#define LCD_DATA4 PIN_B7
#define LCD_DATA5 PIN_B6
#define LCD_DATA6 PIN_B5
#define LCD_DATA7 PIN_B4
#include <lcd.c>
#define trig pin_B1
#define echo input(PIN_B0)
#define on output_high
#define off output_low
#define buzz PIN_C3

int16 get_dist(void)
{
int16 cm=0;
on(trig);
delay_us(50);
off(trig);
set_timer0(0);
while(echo==0 && (get_timer0() < 255));
set_timer0(0);
while(echo==1 && (get_timer0() < 255))
{
cm++;
delay_us(58);
}
delay_ms(50);
return(cm);
}

void main(void)
{
setup_timer_0 (RTCC_INTERNAL | RTCC_DIV_256);
int16 distancia;
lcd_init();
while(true)
{
distancia=get_dist();
if(distancia==0)
{
printf(lcd_putc, "\f");
printf(lcd_putc,"DISTANCIA NaN cm");
off(buzz);
delay_ms(50);
}
else if(distancia>0 && distancia<6)
{
off(buzz);
printf(lcd_putc, "\f");
printf(lcd_putc,"Distancia: %03lucm",distancia);
on(buzz);
delay_ms(50);
}
else if(distancia<=10 && distancia>6)
{
off(buzz);
printf(lcd_putc, "\f");
printf(lcd_putc,"Distancia: %03lucm",distancia);
on(buzz);
delay_ms(200);
off(buzz);
delay_ms(200);
}
else if(distancia>10 && distancia<=20)
{
off(buzz);
printf(lcd_putc, "\f");
printf(lcd_putc,"Distancia: %03lucm",distancia);
on(buzz);
delay_ms(200);
off(buzz);
delay_ms(350);
}
else if(distancia>20 && distancia<=30)
{
off(buzz);
printf(lcd_putc, "\f");
printf(lcd_putc,"Distancia: %03lucm",distancia);
on(buzz);
delay_ms(200);
off(buzz);
delay_ms(550);
}
else if(distancia>30 && distancia<=40)
{
off(buzz);
printf(lcd_putc, "\f");
printf(lcd_putc,"Distancia: %03lucm",distancia);
on(buzz);
delay_ms(200);
off(buzz);
delay_ms(700);
}
else if(distancia>40)
{
off(buzz);
printf(lcd_putc, "\f");
printf(lcd_putc,"Distancia: %03lucm",distancia);
delay_ms(100);
}
}
}
