from flask import Flask
import eospy.cleos

app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello World!"

@app.route("/issue")
def issue():
    # url 자리에 BP 호스트 주소를 넣으면 Jungle, Kylin, Mainnet 등에 붙을 수 있습니다.
    client = eospy.cleos.Cleos(url="https://jungle2.cryptolions.io:443")

    param = {
        "account": "bryantestdev",     # 실행할 Contract가 들어있는 Account
        "name": "issue",               # Action
        "authorization": [{
            "actor": "bryantestdev",   # 실행할 Account ( -p bryanrhee@active)
            "permission": "active"     # 실행할 Account의 권한 (-p bryanrhee@active)
        }]
    }
    args = {
        "to": "bryanrhee",             # Dictionary의 Key - Action의 파라미터 이름
        "quantity":"500.0000 EOS",     # Dictionary의 Value - Action에 들어갈 파라미터 값
        "memo": "Issue!"
    }
    bin_param = client.abi_json_to_bin(param['account'], param['name'], args)    # Parameter를 Binary로 고친 값
    param['data'] = bin_param['binargs']  # Tx의 데이터 부분에 Binary 파라미터 삽입
    trx = {"actions": [param]}

    # Authorization, Actor-permission에 맞는 개인키. 실제 사용시, 절대 코드 내에 직접 삽입하지 말 것!
    key = "5KJrb5cM2c7P4sVbc2pCEjL9vPAgwZCUpBnkxxWsBUvgZWN3SyB"
    resp = client.push_transaction(trx, key, broadcast=True)

    return "Complete"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)

