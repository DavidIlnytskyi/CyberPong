/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#include "project.h"
#include "led.h"
#include <stdio.h>


void chooseSide(uint8 cycles, uint8 sideCoord, uint32 color)
{
    StripLights_DisplayClear(StripLights_BLACK);
	StripLights_MemClear(StripLights_BLACK);
 
    uint32 ledPosition = 1;
    uint8 currCycles = 0;
    uint32 ledPos;
    
    for(int i = 0; i < 7; ++i)
    {
        StripLights_Pixel(i, 0, color);
        StripLights_Trigger(1);  
        CyDelay(50);
    }
    
    uint32 mainCol = StripLights_GetPixel(0, 0);
    uint32 col2 = mainCol;
    col2 = (col2 >> 1) & 0x007F7F7F;
    col2 = (col2 >> 1) & 0x007F7F7F;
    uint32 col3 = col2;
    col3 = (col3 >> 1) & 0x007F7F7F;
    uint32 col4 = col3;
    col4 = (col4 >> 1) & 0x007F7F7F;
    col4 = (col4 >> 1) & 0x007F7F7F;
    
    for(;;)
    {
        StripLights_Pixel((ledPosition+23)%24, 0, StripLights_BLACK);
        
        StripLights_Pixel((ledPosition + 3) % 24, 0, mainCol);
        StripLights_Pixel(ledPosition % 24, 0, col4);
        StripLights_Pixel((ledPosition + 6) % 24, 0, col4);
        StripLights_Pixel((ledPosition + 1) % 24, 0, col3);
        StripLights_Pixel((ledPosition + 5) % 24, 0, col3);
        StripLights_Pixel((ledPosition + 2) % 24, 0, col2);
        StripLights_Pixel((ledPosition + 4) % 24, 0, col2);
        
        StripLights_Trigger(1);  
        CyDelay(50);
        ledPosition = (ledPosition + 1) % 24;
        if(ledPosition == sideCoord)
        {
            currCycles++;
        }
        if(currCycles == cycles)
        {
            break;
        }
    }

}


void chooseDiffIdle(uint32 startColor)
{
    uint32 color = startColor;
	uint32 nextColor = 0;
	uint32 pct = 0;
	uint32 toColor, fromColor, newColor;
	uint32 ledPosition = 0;     
	UART_UartPutString("-----------------");
    
    for(;;)
    {   
		nextColor = color + 1;
		if(nextColor >= StripLights_COLOR_WHEEL_SIZE) nextColor = 0;
		
		fromColor = StripLights_CLUT[color];
		toColor   = StripLights_CLUT[nextColor];  
        
		for(pct = 0; pct <= 100; pct += 10)
		{
		    newColor  = (((pct * (toColor & 0x00FF0000)) + ((100-pct) * (fromColor & 0x00FF0000)))/100) & 0x00FF0000;
            newColor |= (((pct * (toColor & 0x0000FF00)) + ((100-pct) * (fromColor & 0x0000FF00)))/100) & 0x0000FF00;
            newColor |= (((pct * (toColor & 0x000000FF)) + ((100-pct) * (fromColor & 0x000000FF)))/100) & 0x000000FF;
            if(newColor == 255 && pct) return;
            char freqStr[100];
            sprintf(freqStr, "%lu %lu color: %lu\r\n", newColor, pct, color);
            UART_UartPutString(freqStr);
			
			while( !StripLights_Ready() ); 
			
	        for(ledPosition = 0; ledPosition <= StripLights_TOTAL_LEDS; ledPosition++)
	        {
	            StripLights_Pixel(ledPosition, 0, newColor % 65536);
	        }
 		
	  	    StripLights_Trigger(1); 
			
			CyDelay(20);
	    } 
		color++;  
        if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;
    }
}

void chooseDifficulty(uint32 diffColor)
{
    for(int i = 0; i < 3; ++i)
    {
        for(uint32 j = 0; j < 24; ++j)
        {
            StripLights_Pixel(j, 0, diffColor);
        }
        StripLights_Trigger(1);
        CyDelay(350);
        
        for(uint32 j = 0; j < 24; ++j)
        {
            StripLights_Pixel(j, 0, 0);
        }
        StripLights_Trigger(1);
        CyDelay(350);
    }
}


void start()
{
    StripLights_DisplayClear(StripLights_BLACK);
	StripLights_MemClear(StripLights_BLACK);
    for(uint32 i = 0; i < 255; ++i)
    {
        for(uint32 j = 0; j < 24; ++j)
        {
            StripLights_Pixel(j, 0, i);
        }
        StripLights_Trigger(1);
        CyDelay(10);
    }
}

void end()
{
    for(int32 i = 255; i >= 0; --i)
    {
        for(uint32 j = 0; j < 24; ++j)
        {
            StripLights_Pixel(j, 0, i);
        }
        StripLights_Trigger(1);
        CyDelay(10);
    }
}

void oneColor(uint32 color)
{
    StripLights_DisplayClear(StripLights_BLACK);
    StripLights_MemClear(StripLights_BLACK);
    
    StripLights_Pixel(0, 0, StripLights_BLACK);
    for(int i = 0; i < 24; ++i)
    {
        StripLights_Pixel(i, 0, color);
    }
    CyDelay(10);
    StripLights_Trigger(1); 
}

/* [] END OF FILE */
