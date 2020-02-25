import unittest
import subprocess
import re
import random
from pathlib import Path


my_pos = Path(__file__).parent.absolute()

all_champs_path = Path(my_pos/'champs').glob('**/*')
all_champs = [x for x in all_champs_path]

CHAMP_PATH = ['./champs/bigzork.cor', './champs/zork.cor', './champ_path/turtle.cor', './champs/Gagnant.cor']

def get_my_dump(dump_cyle, champ_path):
    try:
        command_lst = ['./corewar', '-dump']
        for x in champ_path:
            command_lst.insert(1, x)
        command_lst.append(str(dump_cyle))
        dump = subprocess.run(command_lst, capture_output=True)

        return (dump.stdout.decode('utf-8'))
    except Exception as e:
        print('faild to get dump, reason:' , e)
        exit()

def get_zaz_dump(dump_cyle, champ_path):
    try:
        command_lst = ['./champs/zaz_corewar', '-d']
        for x in champ_path:
            command_lst.insert(1, x)
        command_lst.append(str(dump_cyle))
        dump = subprocess.run(command_lst, capture_output=True)
        return (dump.stdout.decode('utf-8'))
    except Exception as e:
        print('faild to get dump, reason:' , e)
        exit()

def strip_useless(string):
    string = re.sub('0x\w{4} : ', '', string)
    string = re.sub('\s', '', string)
    return (string)

def get_the_2_dump(dump_cyle, champ_path):
    my_dump = get_my_dump(dump_cyle, champ_path)
    my_dump = strip_useless(my_dump)
    zaz_dump = get_zaz_dump(dump_cyle, champ_path)
    zaz_dump = strip_useless(zaz_dump)
    return (my_dump, zaz_dump)


class TestDump(unittest.TestCase):
    # def setUp(self, champ_path):
    #     self.champ_path = C

    maxDiff=None
    def test_dump_output(self, maxDiff=None):
        for i in range(0,1):
            dump_cyle = random.randint(0, 10000)
            # print('tested dump_cyle is:', dump_cyle)
            my_dump, zaz_dump = get_the_2_dump(dump_cyle, CHAMP_PATH)
            with self.subTest(i=dump_cyle):
                self.assertEqual(my_dump, zaz_dump)




if __name__ == '__main__':
    subprocess.run(['make'])
    print(all_champs)

    # unittest.main()
