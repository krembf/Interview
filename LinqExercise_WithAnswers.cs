using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace CodeSmorgasbord.Linq
{
    public static class LinqExercise_WithAnswers
    {
        public static void LinqExample0()
        {
            //No Linq yet

            string[] names = { "Alice", "Bob", "John" };

            //Save all names that have length of 4 or more characters
            IList<string> filteredNames = new List<string>();
            foreach (string name in names)
            {
                if (name.Length >= 4)
                    filteredNames.Add(name);
            }
        }

        public static void LinqExample1()
        {
            //Same as LinqExample0, but with Linq

            string[] names = { "Alice", "Bob", "John" };

            IEnumerable<string> filteredNames1 = System.Linq.Enumerable.Where(names, n => n.Length >= 4);

            IEnumerable<string> filteredNames2 = names.Where(n => n.Length >= 4);

            var filteredNames3 = names.Where(n => n.Length >= 4);

            var filteredNames4 = from name in names
                                 where name.Length >= 4
                                 select name;
        }

        public static void LinqExample2()
        {
            // Given the following dictionary, find and return Russian translations containing two words:

            IDictionary<string, string> vocabulary = new Dictionary<string, string> 
            {
                { "Hello", "Privet"},
                { "Goodbye", "Do Svidanya" },
                { "Good Morning", "Dobriy Den"}
            };

            //Method syntax
            var doubleWords = vocabulary
                .Where(word => word.Key.Contains(' ') && word.Value.Contains(' '))
                .Select(word => word.Value).ToList();
            Console.WriteLine(string.Join(",", doubleWords));

            //Query syntax
            doubleWords = (from word in vocabulary
                           where word.Key.Contains(' ') && word.Value.Contains(' ')
                           select word.Value).ToList();
            Console.WriteLine(string.Join(",", doubleWords));
        }

        public static void LinqExample3()
        {
            //Get all even numbers occurrences from collection

            IList<int> numbers = new List<int>(new int[] { 1, 2, 3, 4, 6 });

            IList<int> evenNumbers = numbers.Where(num => num%2 == 0).ToList();
        }

        public static void LinqExample4()
        {
            //What are the contents of a, b and c after the following initializations?

            int[] a = Enumerable.Repeat(-1, 10).ToArray();
            int[] b = Enumerable.Range(0, 10).ToArray();
            int[] c = Enumerable.Range(0, 10).Select(i => 100 + 10 * i).ToArray();
        }

        public static void LinqExample5()
        {
            //Create random sequence
            var random = new Random();
            int[] randomSequence = Enumerable.Repeat(0, 10).Select(n => n = random.Next() % 100).ToArray();
        }

        public static void LinqExample6()
        {
            //Generate a string ABCABCABC...
            var repeatedStringArray = Enumerable.Repeat("ABC", 10).ToArray();
            var repeatedString = string.Join(string.Empty, repeatedStringArray);
        }

        public static void LinqExample7()
        {
            //Lazy Execution
            IList<int> numbers = new List<int>(new int[] { 1, 2 });

            var powers = numbers.Select(n => n * n);

            numbers.Add(3);

            foreach (int power in powers)
            {
                Console.WriteLine(string.Format("{0},", power));
            }
        }

        public static void LinqExample8()
        {
            //Eager Execution
            IList<int> numbers = new List<int>(new int[] { 1, 2 });

            var powers = numbers.Select(n => n * n);

            numbers.Add(3);

            foreach (int power in powers)
            {
                Console.WriteLine(string.Format("{0},", power));
            }
        }

        public static void LinqExample9()
        {
            //Aggregate and print string collection using Aggregate and function

            const string delimiter = ",";
            var items = new List<string>() { "foo", "boo", "john", "doe" };

            //Example with Linq
            //Problem is that above Linq method does not work with empty or single-element list.
            //it will throw an InvalidOperationException in case items is empty.
            var sw = Stopwatch.StartNew();
            Console.WriteLine(items.Aggregate((i, j) => i + delimiter + j));
            sw.Stop();
            Console.WriteLine("Time taken: " + sw.Elapsed.TotalMilliseconds + "ms");

            //Example with no LINQ
            sw = Stopwatch.StartNew();
            string.Join(delimiter, items);
            sw.Stop();
            Console.WriteLine("Time taken: " + sw.Elapsed.TotalMilliseconds + "ms");
        }
    }

}
