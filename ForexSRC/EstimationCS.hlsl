
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

int EstimateBuy(int from)
{
    int _lifetime = 0;
    int _counter = 0;
    int _min = Min[from];
    int _candle = at[from];
    int _profit = 0.0f;
    int _tptp = 0.05f * TP * Shrink(amplitude[from]);
    int _timeout = 10 * Range;
    
    float LL = 999999.9f;
    int iter;
    for (iter = at[from]-Range; iter < at[from]; ++iter)
    {
        if (Low[iter] < LL)
            LL = Low[iter];
    }
    for (iter = from; at[iter] == at[from]; --iter)
    {
        if (Bid[iter] < LL)
            LL = Bid[iter];
    }
    
    for (int i = from; i < Total; ++i)
    {
        if (_candle != at[i])
        {
            _candle = at[i];
            
            ++_lifetime;
            if (_lifetime >= _timeout)
                return i;
        }
            
        _profit = Shrink(Bid[i] - Ask[from]);
        if (_profit >= _tptp || Bid[i] <= LL)
            return i;
        
    }
    return 0;
}

int EstimateSell(int from)
{
    int _counter = 0;
    int _lifetime = 0;
    int _min = Min[from];
    int _candle = at[from];
    int _profit = 0.0f;
    int _tptp = 0.05f * TP * Shrink(amplitude[from]);
    int _timeout = 10 * Range;
    
    float HH = -999999.9f;
    int iter;
    for (iter = at[from] - Range; iter < at[from]; ++iter)
    {
        if (High[iter] > HH)
            HH = High[iter];
    }
    for (iter = from; at[iter] == at[from]; --iter)
    {
        if (Bid[iter] > HH)
            HH = Bid[iter];
    }
    
    for (int i = from; i < Total; ++i)
    {
        if (_candle != at[i])
        {
            _candle = at[i];
            
            ++_lifetime;
            if (_lifetime >= _timeout)
                return i;
        }
        
        _profit = Shrink(Bid[from] - Ask[i]);
        if (_profit >= _tptp || Bid[i] >= HH)
            return i;
    }
    return 0;
}


[numthreads(768, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint current = DTid.x + DTid.x * DTid.y;
    if (output[current].closeID == 0)
    {
        if (output[current].orderType == 1)
        {
            output[current].closeID = EstimateBuy(current);
        }
        else if (output[current].orderType == 2)
        {
            output[current].closeID = EstimateSell(current);
        }
    }
}