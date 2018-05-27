#include "face.h"

void face_init() {
    Py_Initialize();
    PyModule = PyImport_ImportModule("face_recognition"); // import face_recognition

    PyLoad_image = PyObject_GetAttrString(PyModule, "load_image_file"); // register functions
    PyFace_encodings = PyObject_GetAttrString(PyModule, "face_encodings");
    PyCompare_faces = PyObject_GetAttrString(PyModule, "compare_faces");

}

void load_image(char *filename, int check) { 
    PyObject *PyFilent ame = PyBytes_FromString(filename);

    PyArg1 = PyTuple_New(1);
    PyTuple_SetItem(PyArg1, 0, PyFilename); // conver list to Tuple

    if(PyLoad_image && PyCallable_Check(PyLoad_image)) {
        if (check == 0) { // userimage
            PyUser = PyObject_CallObject(PyLoad_image, PyArg1);

        }
        else { // picture image
            PyPicture = PyObject_CallObject(PyLoad_image, PyArg1);
        }
    }
    else
        PyErr_Print();
}

void face_encoding(PyObject *image,int check) {
    PyArg1 = PyTuple_New(1);
    PyTuple_SetItem(PyArg1, 0, image);

    if (PyFace_encodings && PyCallable_Check(PyFace_encodings)) {
        if (check == 0) 
            PyEnc1 = PyObject_CallObject(PyFace_encodings, PyArg1);
        else
            PyEnc2 = PyObject_CallObject(PyFace_encodings, PyArg1);
    }
    else 
        PyErr_Print();
}

int face_compare(double tolerance) {
    first_enc1 = PyList_GetItem(PyEnc1, 0);
    first_enc2 = PyList_GetItem(PyEnc2, 0);
    PyArg1 = PyList_New(1);
    PyList_SetItem(PyArg1, 0, first_enc1); // make list

    PyArg2 = PyFloat_FromDouble(tolerance);

    if (PyCompare_faces && PyCallable_Check(PyCompare_faces)) {
        ret = PyObject_CallFunctionObjArgs(PyCompare_faces, PyArg1, first_enc2, PyArg2, NULL);
        if (ret != NULL) 
            printf("face compare success\n");
        else
            PyErr_Print();
    }

    return 1;
}
