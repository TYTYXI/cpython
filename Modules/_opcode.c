#include "Python.h"
#include "compile.h"
#include "opcode.h"
#include "internal/pycore_code.h"

/*[clinic input]
module _opcode
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=117442e66eb376e6]*/

#include "clinic/_opcode.c.h"

/*[clinic input]

_opcode.stack_effect -> int

  opcode: int
  oparg: object = None
  /
  *
  jump: object = None

Compute the stack effect of the opcode.
[clinic start generated code]*/

static int
_opcode_stack_effect_impl(PyObject *module, int opcode, PyObject *oparg,
                          PyObject *jump)
/*[clinic end generated code: output=64a18f2ead954dbb input=461c9d4a44851898]*/
{
    int oparg_int = 0;
    int jump_int;

    if (oparg != Py_None) {
        oparg_int = (int)PyLong_AsLong(oparg);
        if ((oparg_int == -1) && PyErr_Occurred()) {
            return -1;
        }
    }

    if (jump == Py_None) {
        jump_int = -1;
    }
    else if (jump == Py_True) {
        jump_int = 1;
    }
    else if (jump == Py_False) {
        jump_int = 0;
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                "stack_effect: jump must be False, True or None");
        return -1;
    }
    int effect = PyCompile_OpcodeStackEffectWithJump(opcode, oparg_int, jump_int);
    if (effect == PY_INVALID_STACK_EFFECT) {
        PyErr_SetString(PyExc_ValueError, "invalid opcode or oparg");
        return -1;
    }
    return effect;
}

/*[clinic input]

_opcode.is_valid -> bool

  opcode: int

Return True if opcode is valid, False otherwise.
[clinic start generated code]*/

static int
_opcode_is_valid_impl(PyObject *module, int opcode)
/*[clinic end generated code: output=b0d918ea1d073f65 input=fe23e0aa194ddae0]*/
{
    return PyUnstable_OpcodeIsValid(opcode);
}

/*[clinic input]

_opcode.has_arg -> bool

  opcode: int

Return True if the opcode uses its oparg, False otherwise.
[clinic start generated code]*/

static int
_opcode_has_arg_impl(PyObject *module, int opcode)
/*[clinic end generated code: output=7a062d3b2dcc0815 input=93d878ba6361db5f]*/
{
    return PyUnstable_OpcodeIsValid(opcode) &&
           PyUnstable_OpcodeHasArg(opcode);
}

/*[clinic input]

_opcode.has_const -> bool

  opcode: int

Return True if the opcode accesses a constant, False otherwise.
[clinic start generated code]*/

static int
_opcode_has_const_impl(PyObject *module, int opcode)
/*[clinic end generated code: output=c646d5027c634120 input=a6999e4cf13f9410]*/
{
    return PyUnstable_OpcodeIsValid(opcode) &&
           PyUnstable_OpcodeHasConst(opcode);
}

/*[clinic input]

_opcode.has_name -> bool

  opcode: int

Return True if the opcode accesses an attribute by name, False otherwise.
[clinic start generated code]*/

static int
_opcode_has_name_impl(PyObject *module, int opcode)
/*[clinic end generated code: output=b49a83555c2fa517 input=448aa5e4bcc947ba]*/
{
    return PyUnstable_OpcodeIsValid(opcode) &&
           PyUnstable_OpcodeHasName(opcode);
}

/*[clinic input]

_opcode.has_jump -> bool

  opcode: int

Return True if the opcode has a jump target, False otherwise.
[clinic start generated code]*/

static int
_opcode_has_jump_impl(PyObject *module, int opcode)
/*[clinic end generated code: output=e9c583c669f1c46a input=35f711274357a0c3]*/
{
    return PyUnstable_OpcodeIsValid(opcode) &&
           PyUnstable_OpcodeHasJump(opcode);

}

/*[clinic input]

_opcode.get_specialization_stats

Return the specialization stats
[clinic start generated code]*/

static PyObject *
_opcode_get_specialization_stats_impl(PyObject *module)
/*[clinic end generated code: output=fcbc32fdfbec5c17 input=e1f60db68d8ce5f6]*/
{
#ifdef Py_STATS
    return _Py_GetSpecializationStats();
#else
    Py_RETURN_NONE;
#endif
}

static PyMethodDef
opcode_functions[] =  {
    _OPCODE_STACK_EFFECT_METHODDEF
    _OPCODE_IS_VALID_METHODDEF
    _OPCODE_HAS_ARG_METHODDEF
    _OPCODE_HAS_CONST_METHODDEF
    _OPCODE_HAS_NAME_METHODDEF
    _OPCODE_HAS_JUMP_METHODDEF
    _OPCODE_GET_SPECIALIZATION_STATS_METHODDEF
    {NULL, NULL, 0, NULL}
};

static PyModuleDef_Slot module_slots[] = {
    {Py_mod_multiple_interpreters, Py_MOD_PER_INTERPRETER_GIL_SUPPORTED},
    {0, NULL}
};

static struct PyModuleDef opcodemodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_opcode",
    .m_doc = "Opcode support module.",
    .m_size = 0,
    .m_methods = opcode_functions,
    .m_slots = module_slots,
};

PyMODINIT_FUNC
PyInit__opcode(void)
{
    return PyModuleDef_Init(&opcodemodule);
}
