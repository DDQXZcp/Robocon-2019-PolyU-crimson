# Robocon-2019-PolyU-crimson
Robocon 2019 PolyU crimson full explanation

## Positioning

### Data structure of points

In the init_path() of main.cpp
~~~
points[0] = (pointInfo){.targetPos.x = 0.0948683, .targetPos.y = 0.0316228, .targetPos.w = 0};
~~~

Trace back to main.h

~~~
struct pointInfo points[2000];

struct position targetPos = {
    .x = points[0].targetPos.x,  //  +  startup_offset_x_encoder;
    .y = points[0].targetPos.y,  //  +  startup_offset_y_encoder;
    .w = points[0].targetPos.w * RAD_TO_DEG // -  startup_offset_w_encoder;
};
~~~

Trace back to ActionEncoder.h Then to common.h(There is a bit confusing not to include common.h in main.h, but we also include common.h in ActionEncoder.h, so it doesn't matter

~~~
struct position {
    float x;
    float y;
    float w;
};
struct pointInfo
{
   struct position targetPos;

};
~~~
For struct pointInfo, I would like to say ??? 
Position 
