from flask import Flask,request

app=Flask(__name__)

@app.route('/hello')
def hello():
    name=request.args.get('name','游客') #获取URL中name参数
    return f'hello,{name}!'

if __name__=='__main__':
    app.run(debug=True,host='0.0.0.0',port=1234)


