#include <face.h>

void face_init() {
    printf("face_init start\n");
    Py_Initialize();
    PyModule = PyImport_ImportModule("face_recognition"); // import face_recognition
    
    PyLoad_image = PyObject_GetAttrString(PyModule, "load_image_file"); // register functions
    PyFace_encodings = PyObject_GetAttrString(PyModule, "face_encodings");
    PyCompare_faces = PyObject_GetAttrString(PyModule, "compare_faces");
    printf("face_init complete\n");
        
 //   load_image(USER_FILENAME, 0);
 //   load_image(PIC_FILENAME, 1);
    if (PyUser != NULL)
        face_encoding(PyUser, 0);
    else
        printf("PyUser is NULL\n");

    if (PyPicture == NULL) 
        printf("in face init PyPicture is NULL\n");
    else
        printf("in face init PyPicture is not NULL\n");
        
}

void load_image(char *filename, int check) { 
    printf("file name %s   %d\n", filename, check);
    PyObject *PyFilename = PyBytes_FromString(filename);
    
    PyObject *PyArg = PyTuple_New(1);
    PyTuple_SetItem(PyArg, 0, PyFilename); // conver list to Tuple

    if(PyLoad_image && PyCallable_Check(PyLoad_image)) {
        if (check == 0) { // userimage
            PyUser = PyObject_CallObject(PyLoad_image, PyArg);

        }
        else { // picture image
            PyPicture = PyObject_CallObject(PyLoad_image, PyArg);
        }
    }
    Py_DECREF(PyArg);
   // else
    //    PyErr_Print();
}

void face_encoding(PyObject *image,int check) {
    printf("in face_encoding...\n");
    PyArg1 = PyTuple_New(1);
    PyTuple_SetItem(PyArg1, 0, image);
    if (image == NULL) {
        printf("image is NULL\n");
        return;
    }
    if (PyArg1 == NULL) {
        printf("PyArg1 is NULL\n");
        return ;
    }

    if (PyFace_encodings && PyCallable_Check(PyFace_encodings)) {
        if (check == 0) 
            PyEnc1 = PyObject_CallObject(PyFace_encodings, PyArg1);
        else
            PyEnc2 = PyObject_CallObject(PyFace_encodings, PyArg1);
    }
    if (check == 0 && PyEnc1 == NULL) {
        printf("PyEnc1 is NULL\n");
    }
    if (check == 1 && PyEnc2 == NULL) {
        printf("PyEnc2 is NULL\n"); 
    }
    //else 
   //     PyErr_Print();
    printf("exit face_encoding\n");
}

int face_compare(double tolerance) {
    // loading pictured image and encoding
    if (PyUser == NULL) {
        load_image(USER_FILENAME, 0);
        face_encoding(PyUser, 0);
    }
    load_image(PIC_FILENAME, 1); // iamge load;
    printf("before face_encodng pypicutre\n");
    face_encoding(PyPicture, 1); // encoding

    if (PyEnc1 == NULL) {
        printf("PyEnc1 is null\n");
        return 0;
    }
    if (PyEnc2 == NULL)  {
        printf("PyEnc2 is null\n");
        return 0;
    }

    first_enc1 = PyList_GetItem(PyEnc1, 0);
    first_enc2 = PyList_GetItem(PyEnc2, 0);
    PyArg1 = PyList_New(1);
    PyList_SetItem(PyArg1, 0, first_enc1); // make list

    PyArg2 = PyFloat_FromDouble(tolerance);

    if (PyCompare_faces && PyCallable_Check(PyCompare_faces)) {
        ret = PyObject_CallFunctionObjArgs(PyCompare_faces, PyArg1, first_enc2, PyArg2, NULL);
        if (ret != NULL) 
            printf("face compare success\n");
        else {
            PyErr_Print();
            return 0;
        }
    }

    return 1;
}
