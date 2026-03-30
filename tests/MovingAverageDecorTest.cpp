#include <AUnit.h>
#include "../src/evamSlidingWindowDecor.h"
#include "MockMotor.h"
#include <evaTac.h>

using namespace aunit;
using namespace evam;

// Test 1: Before buffer is full, values pass through unchanged
test(ma_pass_through_before_full)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(100);
    assertEqual(filter.resultLevel, 100);
    
    filter.Go(200);
    assertEqual(filter.resultLevel, 200);
    
    // Still not full (need 3 values)
    filter.Go(300);
    // Now buffer is full, output should be average
    // (100+200+300)/3 = 200
    assertEqual(filter.resultLevel, 200);
}

// Test 2: Average calculation with N=3
test(ma_average_n3)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(10);
    filter.Go(20);
    filter.Go(30);
    
    assertEqual(filter.resultLevel, 20);  // (10+20+30)/3 = 20
}

// Test 3: Moving average updates with each new value
test(ma_moving_update)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    // Fill buffer
    filter.Go(10);  // pass through
    filter.Go(20);  // pass through
    filter.Go(30);  // average = 20
    
    // Add new value, oldest (10) removed
    filter.Go(40);
    // Buffer: [20,30,40], average = (20+30+40)/3 = 30
    assertEqual(filter.resultLevel, 30);
    
    // Add another
    filter.Go(50);
    // Buffer: [30,40,50], average = (30+40+50)/3 = 40
    assertEqual(filter.resultLevel, 40);
}

// Test 4: N=2 (simple two-point average)
test(ma_n2)
{
    SlidingWindowDecor<MockMotor, 2> filter;
    
    filter.Go(100);  // pass through
    filter.Go(200);  // average = (100+200)/2 = 150
    assertEqual(filter.resultLevel, 150);
    
    filter.Go(300);
    // Buffer: [200,300], average = (200+300)/2 = 250
    assertEqual(filter.resultLevel, 250);
    
    filter.Go(400);
    // Buffer: [300,400], average = (300+400)/2 = 350
    assertEqual(filter.resultLevel, 350);
}

// Test 5: N=5
test(ma_n5)
{
    SlidingWindowDecor<MockMotor, 5> filter;
    
    filter.Go(10);
    filter.Go(20);
    filter.Go(30);
    filter.Go(40);
    filter.Go(50);  // average = (10+20+30+40+50)/5 = 30
    
    assertEqual(filter.resultLevel, 30);
    
    filter.Go(60);
    // Buffer: [20,30,40,50,60], average = (20+30+40+50+60)/5 = 40
    assertEqual(filter.resultLevel, 40);
    
    filter.Go(70);
    // Buffer: [30,40,50,60,70], average = (30+40+50+60+70)/5 = 50
    assertEqual(filter.resultLevel, 50);
}

// Test 6: All values same
test(ma_all_same)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(50);
    filter.Go(50);
    filter.Go(50);
    
    assertEqual(filter.resultLevel, 50);
    
    filter.Go(50);
    assertEqual(filter.resultLevel, 50);
}

// Test 7: Negative values
test(ma_negative)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(-10);
    filter.Go(-20);
    filter.Go(-30);
    
    assertEqual(filter.resultLevel, -20);  // (-10-20-30)/3 = -20
    
    filter.Go(-40);
    // Buffer: [-20,-30,-40], average = (-20-30-40)/3 = -30
    assertEqual(filter.resultLevel, -30);
}

// Test 8: Mixed positive and negative
test(ma_mixed)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(-50);
    filter.Go(0);
    filter.Go(50);
    
    assertEqual(filter.resultLevel, 0);  // (-50+0+50)/3 = 0
    
    filter.Go(100);
    // Buffer: [0,50,100], average = (0+50+100)/3 = 50
    assertEqual(filter.resultLevel, 50);
}

// Test 9: Large values (near limits)
test(ma_large_values)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(1000);
    filter.Go(1000);
    filter.Go(1000);
    
    assertEqual(filter.resultLevel, 1000);
    
    filter.Go(-1000);
    // Buffer: [1000,1000,-1000], average = (1000+1000-1000)/3 = 333
    assertEqual(filter.resultLevel, 333);
}

// Test 11: Verify sum doesn't overflow (N=15, max values)
test(ma_sum_overflow)
{
    SlidingWindowDecor<MockMotor, 15> filter;
    
    // Fill with max values
    for (int i = 0; i < 15; i++)
        filter.Go(1000);
    
    // Sum = 15000, fits in signed long (32-bit)
    assertEqual(filter.resultLevel, 1000);
}

// Test 12: Smoothing effect on spikes
test(ma_spike_smoothing)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(10);
    filter.Go(20);
    filter.Go(1000);  // spike
    
    // Average = (10+20+1000)/3 = 343
    assertEqual(filter.resultLevel, 343);
    
    filter.Go(30);
    // Buffer: [20,1000,30], average = (20+1000+30)/3 = 350
    assertEqual(filter.resultLevel, 350);
    
    filter.Go(40);
    // Buffer: [1000,30,40], average = (1000+30+40)/3 = 356
    assertEqual(filter.resultLevel, 356);
    
    filter.Go(50);
    // Buffer: [30,40,50], average = (30+40+50)/3 = 40
    assertEqual(filter.resultLevel, 40);
}

// Test 13: Zero values
test(ma_zero)
{
    SlidingWindowDecor<MockMotor, 3> filter;
    
    filter.Go(0);
    filter.Go(0);
    filter.Go(0);
    
    assertEqual(filter.resultLevel, 0);
    
    filter.Go(100);
    // Buffer: [0,0,100], average = (0+0+100)/3 = 33
    assertEqual(filter.resultLevel, 33);
}


// Test 15: Continuous operation with many values
test(ma_continuous)
{
    SlidingWindowDecor<MockMotor, 3> filter;
        
    filter.Go(100);  // pass through
    assertEqual(filter.resultLevel, 100);
    
    filter.Go(200);  // pass through
    assertEqual(filter.resultLevel, 200);
    
    filter.Go(300);  // average = 200
    assertEqual(filter.resultLevel, 200);
    
    filter.Go(400);  // average = 300
    assertEqual(filter.resultLevel, 300);
    
    filter.Go(500);  // average = 400
    assertEqual(filter.resultLevel, 400);
    
    filter.Go(600);  // average = 500
    assertEqual(filter.resultLevel, 500);
}