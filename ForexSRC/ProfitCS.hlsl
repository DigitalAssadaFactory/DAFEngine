
cbuffer MyParam : register(b0)
{
    int Total, Digits, TP, SL, Stride, Scale, Offset, Range;
    float Fading, HRatio, ARatio, Huge;
};

StructuredBuffer<float> Ask : register(t0);
StructuredBuffer<float> Bid : register(t1);
StructuredBuffer<float> Open : register(t2);
StructuredBuffer<float> Close : register(t3);
StructuredBuffer<float> High : register(t4);
StructuredBuffer<float> Low : register(t5);
StructuredBuffer<int> Year : register(t6);
StructuredBuffer<int> Mon : register(t7);
StructuredBuffer<int> Day : register(t8);
StructuredBuffer<int> Hour : register(t9);
StructuredBuffer<int> Min : register(t10);
StructuredBuffer<int> Sec : register(t11);
StructuredBuffer<int> DoW : register(t12);
StructuredBuffer<int> at : register(t13);

struct MyOutput
{
    int orderType, closeID, lifetime;
    float profit;
};
RWStructuredBuffer<MyOutput> output : register(u0);
RWStructuredBuffer<float> amplitude : register(u1);

inline int Shrink(float x)
{
    return x * pow(10, Digits);
}

inline int ShrinkAbs(float x)
{
    return abs(x * pow(10, Digits));
}


[numthreads(768, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint current = DTid.x + DTid.x * DTid.y;
    if (current < (uint) Total)
    {
        if (output[current].closeID != 0)
        {
            if (output[current].orderType == 1)
            {
                output[current].profit = Bid[output[current].closeID] - Ask[current];
                output[current].lifetime = at[output[current].closeID] - at[current];
            }
            else if (output[current].orderType == 2)
            {
                output[current].profit = Bid[current] - Ask[output[current].closeID];
                output[current].lifetime = at[output[current].closeID] - at[current];
            }
        }
    }   
}