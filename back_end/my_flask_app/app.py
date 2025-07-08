from flask import Flask,request,jsonify

app=Flask(__name__)

@app.route('/')
def welcome():
    return "Welcome"

#GET请求 使用URL查询参数
@app.route('/hello')
def hello():
    name=request.args.get("name",default="my friend") #request.args为字典对象 get获取指定参数名
    return f"Hello,{name}"

#POST请求 提交数据到服务器

#方式一 表单数据 request.from.get()
@app.route('/login',methods=["POST"])
def login():
    username=request.form.get("username")
    password=request.form.get("password")
    return f"Login attempt {username},{password}"

#方式二 JSON数据 request.get_json()
@app.route('/register',methods=["POST"])
def register():
    data=request.get_json()
    username=data.get("username")
    email=data.get("email")
    return jsonify({
        "message":"User registered",
        "user":username,
        "email":email
    }),201 #设置状态码

if __name__==("__main__"):
    app.run(debug=True)