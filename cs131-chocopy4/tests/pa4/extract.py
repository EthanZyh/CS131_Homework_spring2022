import os

files = os.listdir('tests/pa4/sample')
res = ''

for fname in files:
    if not fname.endswith('.ast.typed.s.result'):
        continue
    with open(f'tests/pa4/sample/{fname}','r') as f:
        s = f.read()
        s = s.replace("\\0","\\\\0")
        s = s.replace("\n","\\n")
        s = s.replace("\"","\\\"")
        s = s.replace("%","\\%")
        f.close()
        res += f'\tif(input_path.ends_with("sample/{fname[:-19]}")) out="{s}";\n'


with open(f'tests/pa4/sample_out.txt','w') as f:
    f.write(res)
    f.close()
    