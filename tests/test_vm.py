# from hypothesis import given, strategies as st
import subprocess
import re
import random
from pathlib import Path


base_dir = Path(__file__).absolute().parent.parent


# TEST_CHAMP = ['./champs/zork.cor', './champs/toto.cor']
# TEST_CHAMP = None

def get_all_champs():
    """compile and get all the *.cor """
    # import pdb; pdb.set_trace()
    subprocess.run(["make"], cwd=base_dir)
    s_path = Path(base_dir / "champs").glob("**/*.s")
    all_s = [x for x in s_path]
    for x in all_s:
        subprocess.run([f'{base_dir}/asm', str(x)])
    #all champs
    # champs_path = Path(base_dir / "champs").glob("**/*.cor")

    #one champ OK
    # champs_path = Path(base_dir / "champs").glob("**/turtle.cor")
    # champs_path = Path(base_dir / "champs").glob("**/bee_gees.cor")

    #one champs ERROR
    champs_path = Path(base_dir / "champs").glob("**/toto.cor")

    all_champs = [str(i) for i in champs_path]
    return all_champs


def get_my_dump(dump_cyle, test_champs):
    command = ["./corewar", *test_champs, "-dump", str(dump_cyle)]
    dump = subprocess.run(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=base_dir
    )

    return dump.stdout.decode("utf-8")


def get_zaz_dump(dump_cyle, test_champs):
    command = ["./champs/zaz_corewar", *test_champs, "-d", str(dump_cyle)]
    dump = subprocess.run(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=base_dir
    )
    return dump.stdout.decode("utf-8")



def reformat_zaz_dump(src):
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



def get_the_2_dump(dump_cyle, test_champs):
    my_dump = get_my_dump(dump_cyle, test_champs)
    zaz_dump = get_zaz_dump(dump_cyle, test_champs)
    zaz_dump = reformat_zaz_dump(zaz_dump)
    return (my_dump, zaz_dump)



# test if my dump result is the same with the zaz_vm
@given(
    dump_cyle=st.integers(min_value=0, max_value=5000),
    test_champs=st.sets(st.sampled_from(get_all_champs()), min_size=1, max_size=4),

)
def test_dump_output(dump_cyle, test_champs):
    my_dump, zaz_dump = get_the_2_dump(dump_cyle, test_champs)
    assert my_dump == zaz_dump



def get_my_cycle(test_champs):
    command = ["./corewar", *test_champs, '-v', '|', 'grep', 'Contestant', '-2']
    end_cycle = subprocess.run(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    return dump.stdout.decode("utf-8")

# # @given(
# #     test_champs=st.sets(st.sampled_from(get_all_champs()), min_size=1, max_size=4),
# # )
# def test_end_cycle(test_champs):
#     command = ["./corewar", *test_champs, '-v']

#     out = subprocess.run(
#         command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=base_dir
#     )
#     match = re.search(r'It is now cycl', out)
#     # match = re.search(r'It is now cycle \d*\nContestant', out)
#     if match:
#         my_end_cycle = int(re.search(r'\d*', match))
#         print(my_end_cycle)
#         assert my_end_cycle == 1000

# test_end_cycle(['./champs/zork.cor'])
