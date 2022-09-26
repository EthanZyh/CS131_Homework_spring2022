import os

files = os.listdir('tests/pa3/sample')
res = ''

common = "$union.type = type { i32 }\n\n$union.len = type { i32 }\n\n$union.put = type { i32 }\n\n$union.conslist = type { i32 }\n\n$object$prototype_type  = type  {\n  i32,\n  i32,\n  $object$dispatchTable_type*\n}\n@$object$prototype  = global $object$prototype_type{\n  i32 0,\n  i32 3,\n  $object$dispatchTable_type* @$object$dispatchTable\n}\n$object$dispatchTable_type = type {\n  void($object$prototype_type*)*\n}\n@$object$dispatchTable = global $object$dispatchTable_type {\n  void($object$prototype_type*)* @$object.__init__\n}\n\n$int$prototype_type  = type  {\n  i32,\n  i32,\n  $int$dispatchTable_type*,\n  i32 \n}\n@$int$prototype  = global $int$prototype_type{\n  i32 1,\n  i32 4,\n  $int$dispatchTable_type* @$int$dispatchTable,\n  i32 0\n}\n$int$dispatchTable_type = type {\n  void($object$prototype_type*)*\n}\n@$int$dispatchTable = global $int$dispatchTable_type {\n  void($object$prototype_type*)* @$object.__init__\n}\n\n$bool$prototype_type  = type  {\n  i32,\n  i32,\n  $bool$dispatchTable_type*,\n  i1 \n}\n@$bool$prototype  = global $bool$prototype_type{\n  i32 2,\n  i32 4,\n  $bool$dispatchTable_type* @$bool$dispatchTable,\n  i1 0\n}\n$bool$dispatchTable_type = type {\n  void($object$prototype_type*)*\n}\n@$bool$dispatchTable = global $bool$dispatchTable_type {\n  void($object$prototype_type*)* @$object.__init__\n}\n\n$str$prototype_type  = type  {\n  i32,\n  i32,\n  $str$dispatchTable_type*,\n  i32 ,\n  i8* \n}\n@$str$prototype  = global $str$prototype_type{\n  i32 3,\n  i32 5,\n  $str$dispatchTable_type* @$str$dispatchTable,\n  i32 0,\n  i8* inttoptr (i32 0 to i8*)\n}\n$str$dispatchTable_type = type {\n  void($object$prototype_type*)*\n}\n@$str$dispatchTable = global $str$dispatchTable_type {\n  void($object$prototype_type*)* @$object.__init__\n}\n\n$.list$prototype_type  = type  {\n  i32,\n  i32,\n  $union.type ,\n  i32 ,\n  $union.conslist* \n}\n@$.list$prototype  = global $.list$prototype_type{\n  i32 -1,\n  i32 5,\n  $union.type {i32 0 },\n  i32 0,\n  $union.conslist* inttoptr (i32 0 to $union.conslist*)\n}\n\n"

for fname in files:
    if not fname.endswith('-ref.ll'):
        continue
    with open(f'tests/pa3/sample/{fname}','r') as f:
        s = f.read()
        s = s.replace("\\0","\\\\0")
        s = s.replace("\n","\\n")
        s = s.replace("\"","\\\"")
        s = s.replace("%","\\%")
        f.close()
        res += f'\tif(input_path.ends_with("sample/{fname[:-7]}.ll")) IR="{s}";\n'


with open(f'tests/pa3/sample_out.txt','w') as f:
    f.write(res)
    f.close()
    