
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
    int openID, closeID, lifetime;
    float profit, amplitude;
};

struct Result
{
    int tradeCount;
    float profit;
};

RWStructuredBuffer<MyOutput> output : register(u0);
RWStructuredBuffer<Result> result : register(u1);
RWStructuredBuffer<int> isDone : register(u2);

[numthreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    static int index = 0;
    if (isDone[0] == -1)
    {
        isDone[0] = 0;
        int _HRatio = 20 * (HRatio - 0.5f);
        int _VRatio = 2 * (ARatio - 2.0f);
        int _Range = Range - 10;
        int index = _HRatio + 40 * _VRatio + 40 * 36 * _Range;
    }
            
    
    float profit = 0.0f;
    int tradeCount = 0;
    int j = 0;
    for (int i = isDone[0]; i < Total; ++i)
    {
        ++j;
        if (output[i].openID != 0)
        {
            profit += output[i].profit;
            ++tradeCount;
            if (output[i].closeID > i)
                i = output[i].closeID;
        }
        if (j > 1000000)
        {
            result[index].tradeCount += tradeCount;
            result[index].profit += profit;
            isDone[0] = i;
            return;
        }
    }
    
    result[index].tradeCount += tradeCount;
    result[index].profit += profit;
    
    isDone[0] = -1;
}
