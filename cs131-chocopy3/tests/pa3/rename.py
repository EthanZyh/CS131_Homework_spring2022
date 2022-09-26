import os

files = os.listdir(f'sample')

for fname in files:
    if not fname.endswith('.ll'):
        continue
    os.system(f'mv sample/{fname} sample/{fname.replace(".ll","")}-ref.ll')