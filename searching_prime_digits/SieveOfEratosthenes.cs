public interface ISieve
{
    void ListPrimes(Action<long> callback);
}

public class SieveOfEratosthenes : ISieve
{
    private BitArray Data;
    public int Length => Data.Length;

    public SieveOfEratosthenes(int length)
    {
        Data = new BitArray(length);
        Data.SetAll(true);

        for (int p = 2; p * p < length; p++)
        {
            if (Data[p])
            {
                for (int i = p * p; i < Length; i += p)
                {
                    Data[i] = false;
                }
            }
        }
    }

    public void ListPrimes(Action<long> callback)
    {
        for (int i = 2; i < Length; i++)
        {
            if (Data[i]) callback.Invoke(i);
        }
    }
}

static void TestSieve<T>(long length, 
                         long expectedCount,
                         long expectedSum,
                         long expectedHash)
{
    var sw = Stopwatch.StartNew();
    ISieve sieve = CreateSieve<T>(length);
    long count = 0, sum = 0, hash = 0;
    Action<long> action = (p) => { count++; sum += p; hash = hash * 31 + p; };
    sieve.ListPrimes(action);
    AssertEquals(expectedCount, count);
    AssertEquals(expectedSum, sum);
    AssertEquals(expectedHash, hash);
    Console.WriteLine($"{typeof(T).Name} up to {length:N0} in {sw.Elapsed}");
}

static void TestSieve_1G<T>() =>
    TestSieve<T>(1_000_000_000, 50847534, 24739512092254535, 1480810120364005255);