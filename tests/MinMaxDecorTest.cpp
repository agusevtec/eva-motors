#include <AUnit.h>
#include "evamMinmaxDecor.h"
#include "MockMotor.h"
#include <evaTac.h>

using namespace aunit;
using namespace evam;

// Test 1: Before buffer is full, values pass through unchanged
test(minimax_pass_through_before_full)
{
    MinmaxDecor<MockMotor, 2> filter;  // N=2, buffer size=4
    
    filter.Go(100);
    assertEqual(filter.resultLevel, 100);
    
    filter.Go(200);
    assertEqual(filter.resultLevel, 200);
    
    filter.Go(300);
    assertEqual(filter.resultLevel, 300);
    
    // Still not full (need 4 values for N=2)
    filter.Go(400);
    // Now buffer is full, output should be filtered
    // Chunk0: [100,200] -> max=200, min=100
    // Chunk1: [300,400] -> max=400, min=300
    // minimax = min(200,400)=200, maximin=max(100,300)=300
    // output = (200+300)/2 = 250
    assertEqual(filter.resultLevel, 250);
}


// Test 3: After full, each new value updates output
test(minimax_continuous_update)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    // Fill buffer
    filter.Go(10);  // pass through
    filter.Go(20);  // pass through
    filter.Go(30);  // pass through
    filter.Go(40);  // filtered: 25
    
    // Add new value, oldest (10) overwritten
    filter.Go(100);
    // Buffer: [20,30,40,100]
    // Chunk0: [20,30] -> max=30, min=20
    // Chunk1: [40,100] -> max=100, min=40
    // output = (min(30,100)=30 + max(20,40)=40)/2 = 35
    assertEqual(filter.resultLevel, 35);
    
    // Add another
    filter.Go(0);
    // Buffer: [30,40,100,0]
    // Chunk0: [30,40] -> max=40, min=30
    // Chunk1: [100,0] -> max=100, min=0
    // output = (min(40,100)=40 + max(30,0)=30)/2 = 35
    assertEqual(filter.resultLevel, 35);
}

// Test 4: N=3 (buffer size=9, chunk size=3)
test(minimax_n3)
{
    MinmaxDecor<MockMotor, 3> filter;
    
    // Fill buffer with 9 values
    filter.Go(10);
    filter.Go(20);
    filter.Go(30);   // chunk0: [10,20,30]
    filter.Go(40);
    filter.Go(50);
    filter.Go(60);   // chunk1: [40,50,60]
    filter.Go(70);
    filter.Go(80);
    filter.Go(90);   // chunk2: [70,80,90]
    
    // Chunk0: max=30, min=10
    // Chunk1: max=60, min=40
    // Chunk2: max=90, min=70
    // minimax = min(30,60,90)=30
    // maximin = max(10,40,70)=70
    // output = (30+70)/2=50
    assertEqual(filter.resultLevel, 50);
}

// Test 5: All values same
test(minimax_all_same)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    filter.Go(50);
    filter.Go(50);
    filter.Go(50);
    filter.Go(50);
    
    assertEqual(filter.resultLevel, 50);
}

// Test 6: Decreasing sequence
test(minimax_decreasing)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    filter.Go(100);
    filter.Go(90);
    filter.Go(80);
    filter.Go(70);
    
    // Chunk0: [100,90] -> max=100, min=90
    // Chunk1: [80,70] -> max=80, min=70
    // output = (min(100,80)=80 + max(90,70)=90)/2 = 85
    assertEqual(filter.resultLevel, 85);
}

// Test 7: Alternating values (spikes)
test(minimax_alternating)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    filter.Go(1000);
    filter.Go(-1000);
    filter.Go(1000);
    filter.Go(-1000);
    
    // Chunk0: [1000,-1000] -> max=1000, min=-1000
    // Chunk1: [1000,-1000] -> max=1000, min=-1000
    // output = (1000 + -1000)/2 = 0
    assertEqual(filter.resultLevel, 0);
}

// Test 8: Negative values only
test(minimax_negative)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    filter.Go(-10);
    filter.Go(-20);
    filter.Go(-30);
    filter.Go(-40);
    
    // Chunk0: [-10,-20] -> max=-10, min=-20
    // Chunk1: [-30,-40] -> max=-30, min=-40
    // output = (min(-10,-30)=-30 + max(-20,-40)=-20)/2 = -25
    assertEqual(filter.resultLevel, -25);
}

// Test 9: Mixed positive and negative
test(minimax_mixed)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    filter.Go(-50);
    filter.Go(100);
    filter.Go(-30);
    filter.Go(200);
    
    // Chunk0: [-50,100] -> max=100, min=-50
    // Chunk1: [-30,200] -> max=200, min=-30
    // output = (min(100,200)=100 + max(-50,-30)=-30)/2 = 35
    assertEqual(filter.resultLevel, 35);
}

// Test 10: Large N=4
test(minimax_n4)
{
    MinmaxDecor<MockMotor, 4> filter;
    
    // Fill buffer with 16 values (4 chunks of 4)
    for (int i = 1; i <= 16; i++)
        filter.Go(i * 10);
    
    // Chunk0: [10,20,30,40] -> max=40, min=10
    // Chunk1: [50,60,70,80] -> max=80, min=50
    // Chunk2: [90,100,110,120] -> max=120, min=90
    // Chunk3: [130,140,150,160] -> max=160, min=130
    // minimax = min(40,80,120,160)=40
    // maximin = max(10,50,90,130)=130
    // output = (40+130)/2 = 85
    assertEqual(filter.resultLevel, 85);
}

// Test 12: Edge case - zero values
test(minimax_zeros)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    filter.Go(0);
    filter.Go(0);
    filter.Go(0);
    filter.Go(0);
    
    assertEqual(filter.resultLevel, 0);
}

// Test 13: Spike rejection
test(minimax_spike_rejection)
{
    MinmaxDecor<MockMotor, 2> filter;
    
    // Normal values with one huge spike
    filter.Go(10);
    filter.Go(20);
    filter.Go(1000);  // spike
    filter.Go(30);
    
    // Buffer: [10,20,1000,30]
    // Chunk0: [10,20] -> max=20, min=10
    // Chunk1: [1000,30] -> max=1000, min=30
    // output = (min(20,1000)=20 + max(10,30)=30)/2 = 25
    assertEqual(filter.resultLevel, 25);
}
