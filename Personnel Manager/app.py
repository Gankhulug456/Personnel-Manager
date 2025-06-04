import ctypes
lib = ctypes.CDLL('./libpersonnel.so')
class PERSONNEL_REC(ctypes.Structure):
    _fields_ = [
        ('last_name', ctypes.c_char_p),
        ('first_name', ctypes.c_char_p),
        ('middle_initial', ctypes.c_char),
        ('age', ctypes.c_int),
        ('salary', ctypes.c_int),
        ('id_type', ctypes.c_long),
    ]

lib.add_record.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char, ctypes.c_int, ctypes.c_long, ctypes.c_int]
lib.add_record.restype = None

lib.get_records_sorted_by_name.argtypes = [ctypes.POINTER(ctypes.c_int)]
lib.get_records_sorted_by_name.restype = ctypes.POINTER(ctypes.POINTER(PERSONNEL_REC))

lib.get_records_sorted_by_age.argtypes = [ctypes.POINTER(ctypes.c_int)]
lib.get_records_sorted_by_age.restype = ctypes.POINTER(ctypes.POINTER(PERSONNEL_REC))

lib.get_records_sorted_by_salary.argtypes = [ctypes.POINTER(ctypes.c_int)]
lib.get_records_sorted_by_salary.restype = ctypes.POINTER(ctypes.POINTER(PERSONNEL_REC))

lib.get_records_sorted_by_id.argtypes = [ctypes.POINTER(ctypes.c_int)]
lib.get_records_sorted_by_id.restype = ctypes.POINTER(ctypes.POINTER(PERSONNEL_REC))

lib.free_all_records.restype = None

def add_record(last_name, first_name, middle_initial, age, id_type, salary):
    lib.add_record(last_name.encode(), first_name.encode(), middle_initial.encode(), age, id_type, salary)

def get_records(sort_key):
    count = ctypes.c_int()
    if sort_key == 'name':
        arr_ptr = lib.get_records_sorted_by_name(ctypes.byref(count))
    elif sort_key == 'age':
        arr_ptr = lib.get_records_sorted_by_age(ctypes.byref(count))
    elif sort_key == 'salary':
        arr_ptr = lib.get_records_sorted_by_salary(ctypes.byref(count))
    elif sort_key == 'id':
        arr_ptr = lib.get_records_sorted_by_id(ctypes.byref(count))
    else:
        raise ValueError('Invalid sort key')

    n = count.value
    if n == 0:
        return []

    records = []
    for i in range(n):
        rec_ptr = arr_ptr[i]
        rec = rec_ptr.contents
        records.append({
            'last_name': rec.last_name.decode(),
            'first_name': rec.first_name.decode(),
            'middle_initial': rec.middle_initial.decode(),
            'age': rec.age,
            'salary': rec.salary,
            'id_type': rec.id_type,
        })
    return records

def free_all():
    lib.free_all_records()

from flask import Flask, request, jsonify, render_template
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    personnel_list = get_records('name')  
    return render_template('index.html', personnel=personnel_list)

@app.route('/add_record', methods=['POST'])
def add_record_route():
    data = request.json
    try:
        add_record(
            data['last_name'],
            data['first_name'],
            data['middle_initial'],
            int(data['age']),
            int(data['id_type']),
            int(data['salary'])
        )
        return jsonify(success=True)
    except Exception as e:
        return jsonify(success=False, error=str(e))

@app.route('/list')
def list_records():
    count = ctypes.c_int()
    records_ptr = lib.get_records_sorted_by_name(ctypes.byref(count))
    num_records = count.value

    personnel_list = []
    for i in range(num_records):
        rec_ptr = ctypes.cast(records_ptr[i], ctypes.POINTER(PERSONNEL_REC))
        personnel_list.append({
            'first_name': rec_ptr.contents.first_name.decode(),
            'last_name': rec_ptr.contents.last_name.decode(),
            'middle_initial': rec_ptr.contents.middle_initial.decode(),
            'age': rec_ptr.contents.age,
            'id_type': rec_ptr.contents.id_type,
            'salary': rec_ptr.contents.salary,
        })

    return render_template('list.html', personnel=personnel_list)
@app.route('/api/list')
def api_list():
    sort_key = request.args.get('sort', 'name')
    try:
        personnel_list = get_records(sort_key)
    except ValueError:
        return jsonify([])  
    return jsonify(personnel_list)


if __name__ == '__main__':
    app.run(debug=True)
