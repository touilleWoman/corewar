from hypothesis import given, strategies as st
import subprocess
import re
import random
from pathlib import Path



# TEST_CHAMP = ['./champs/zork.cor', './champs/toto.cor']
# TEST_CHAMP = None

def get_all_champs():
    """compile and get all the *.cor """
    # import pdb; pdb.set_trace()
    base_dir = Path(__file__).absolute().parent.parent
    subprocess.run(["make"], cwd=base_dir)
    s_path = Path(base_dir / "champs").glob("**/*.s")
    all_s = [x for x in s_path]
    for x in all_s:
        subprocess.run([f'{base_dir}/asm', str(x)])
    champs_path = Path(base_dir / "champs").glob("**/*.cor")
    all_champs = list(champs_path)
    return all_champs


def get_my_dump(dump_cyle, champ_path):
    command_lst = ["./corewar", *champ_path, "-dump", str(dump_cyle)]
    dump = subprocess.run(
        command_lst, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    return dump.stdout.decode("utf-8")


def get_zaz_dump(dump_cyle, champ_path):
    command_lst = ["./champs/zaz_corewar", *champ_path, "-d",str(dump_cyle) ]
    dump = subprocess.run(
        command_lst, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    return dump.stdout.decode("utf-8")



def strip_useless(src):
    # string = re.sub(r"0x\w{4} : ", "", string)
    # string = re.sub("\n", "", string)

    ret = []
    for l in src.split('\n'):
        match = re.match(r"^0x([0-9a-f]{4}) :(( [0-9a-f]{2}){32})(( [0-9a-f]{2}){32}) $", l)
        if not match:
            ret.append(l)
        else:
            addr, l1, _, l2, _ = match.groups()
            addr = int(addr, 16)
            ret.append(f"0x{addr:0>4x} :{l1} ")
            ret.append(f"0x{(addr+32):0>4x} :{l2} ")

    return '\n'.join(ret)



def get_the_2_dump(dump_cyle, champ_path):
    my_dump = get_my_dump(dump_cyle, champ_path)
    zaz_dump = get_zaz_dump(dump_cyle, champ_path)
    zaz_dump = strip_useless(zaz_dump)
    return (my_dump, zaz_dump)




@given(
    dump_cyle=st.integers(min_value=1, max_value=10000),
    test_champs=st.sets(st.sampled_from(get_all_champs()), min_size=1, max_size=4),
)
def test_dump_output(dump_cyle, test_champs):
    my_dump, zaz_dump = get_the_2_dump(dump_cyle, test_champs)
    assert my_dump == zaz_dump

