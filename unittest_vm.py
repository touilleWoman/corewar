import unittest
import subprocess
import re
import random
from pathlib import Path
my_pos = Path(__file__).parent.absolute()
champ_path = my_pos/'champs'



TEST_NB_CHAMPS = 1
DUMP_CYCPLE = None
TEST_CHAMP = ['./champs/zork.cor', './champs/toto.cor']
# TEST_CHAMP = ['./champs/zork.cor']
# TEST_CHAMP = None




def get_all_champs():
    """compile and get all the *.cor """
    subprocess.run(['make'])
    my_pos = Path(__file__).parent.absolute()
    champs_path = Path(my_pos/'champs').glob('**/*.cor')
    s_path = Path(my_pos/'champs').glob('**/*.s')
    all_s = [x for x in s_path]
    for x in all_s:
        subprocess.run(['./asm', str(x)], capture_output=True)
        # uncomment this line to see asm error message
        # subprocess.run(['./asm', str(x)])
    all_champs = [x for x in champs_path]
    return(all_champs)




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
    if TEST_CHAMP is not None:
        champ_path = TEST_CHAMP
    print('=============test_champs===============')
    print(champ_path)
    my_dump = get_my_dump(dump_cyle, champ_path)
    my_dump = strip_useless(my_dump)
    zaz_dump = get_zaz_dump(dump_cyle, champ_path)
    zaz_dump = strip_useless(zaz_dump)
    return (my_dump, zaz_dump)

def get_certain_champs(all_champs, nb):
    lst = []
    for x in range(0, nb):
        lst.append(str(random.choice(all_champs)))
    return lst

all_champs = get_all_champs()
test_champs = get_certain_champs(all_champs, TEST_NB_CHAMPS)

class TestDump(unittest.TestCase):

    maxDiff=None
    def test_dump_output(self, maxDiff=None):
        for i in range(0,1):
            dump_cyle = random.randint(0, 10000)

            if DUMP_CYCPLE is not None:
                dump_cyle = DUMP_CYCPLE

            print('dump_cyle is:', dump_cyle)
            my_dump, zaz_dump = get_the_2_dump(dump_cyle, test_champs)
            with self.subTest(i=dump_cyle):
                self.assertEqual(my_dump, zaz_dump)




if __name__ == '__main__':
    unittest.main()


    # print(all_champs)

    # unittest.main()
