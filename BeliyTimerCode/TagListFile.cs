using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace BeliyTimer
{
    class TagListFile
    {
        List<string> items;
        public List<string> getItems(string fileName)
        {
            items = new List<string>(File.ReadAllLines(fileName));
            return items;
        }
        public void saveItems(string fileName, List<string> list)
        {
            File.WriteAllLines(fileName, list);
        }
        public void checkFile(string fileName)
        {
            if (!File.Exists(fileName))
            {
                FileStream fs = File.Create(fileName);
                fs.Close();
            }
        }
    }
}
