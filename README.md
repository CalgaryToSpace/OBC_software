# Notes about Multi-Threaded Blinky

## Configuration (How I set it up, you can just clone and build, and it should work)
1. In IOC File, in Pinout & Configuration, Middleware and Software packs, select **FREERTOS**
2. For Interface, select CMSIS_V2
3. In configuration, **Select Config Parameters** 
    1. Ensure that USE_PREEMPTION is ennable, I left everything else to default
    2. You can add any tasks (same as processes) by going to the Tasks and Queues Pane
4. FreeRtos requires a systick, but stm also requires it, so we will now configure Timers
    1. Select System Core on the left Nav Bar
    2. Select **SYS**
    3. At the bottom of the **Mode** pane, there is a **Timebase Source** option. For our purposes here, we can use TIM6