using System;
using System.Linq;
using System.Threading;

class Program
{
    static void PrintNumbers(object id)
    {
        for (int i = 0; i < 5; i++)
        {
            Console.WriteLine($"Thread {id}: {i}");
            Thread.Sleep(100);
        }
    }
    static void PrintMessage(object state)
    {
        Console.WriteLine($"ThreadPool thread: {state}");
    }

    static void Main()
    {
        //Using thread (Manual Threading)
        Thread t1 = new Thread(PrintNumbers);
        Thread t2 = new Thread(PrintNumbers);

        t1.Start(1);
        t2.Start(2);

        t1.Join();
        t2.Join();
        Console.WriteLine("Finished Manual Threading");
        //Using thread (Manual Threading)

        //Using ThreadPool
        for (int i = 0; i < 5; i++)
        {
            ThreadPool.QueueUserWorkItem(PrintMessage, $"Task {i}");
        }

        Thread.Sleep(500); // Wait for all threads to finish
        Console.WriteLine("Finished ThreadPool");
        //Using ThreadPool

        //Using Parallel.For and PLINQ
        // Parallel.For
        Parallel.For(0, 5, i =>
        {
            Console.WriteLine($"Parallel.For: {i}");
        });

        // PLINQ - AsParallel().Sum()
        var numbers = Enumerable.Range(1, 1000);
        var sum = numbers.AsParallel().Sum();
        Console.WriteLine($"PLINQ Sum: {sum}");

        Console.WriteLine("Finished Parallel.For & PLINQ");
        //Usinf Paralell.For and PLINQ
    }
}

