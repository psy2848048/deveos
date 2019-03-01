# Private EOSIO가 JSON RPC API Request를 받을 수 있게 하는 파라미터
1. --http-server-address "0.0.0.0:8888" : IP는 방화벽 개념, 포트는 nodeos가 사용할 Port
1. --https-server-address "0.0.0.0:8888" : HTTPS 용
1. --http-alias : IP가 아닌 도메인주소를 사용하는 경우, 해당 도메인으로만 Request를 받을 수 있게 해줌. HTTPS 대비
1. --http-validate-host : http-alias, http-server-address같은 옵션 설정을 엄격히 적용하느냐 마느냐 (true / false)
1. --https-certificate-chain-file: HTTPS 적용시 인증서 chain 파일
1. --https-private-key-file: HTTPS 적용시 Key 파일

# Tx를 JSON RPC로 넣기 위해선..
1. 지갑을 Unlock한다
1. 최근 블록의 정보를 받아온다
1. Parameter를 Binary로 전환한다
1. Tx를 구성한다
1. Signature를 받아 Tx에 삽입한다
1. Push Action을 한다.

# Backend 서버와 EOSIO를 붙이는 방법
1. Contract를 개발하여 Mainnet / Testnet에 Deploy한다
1. Nodejs - eosjs2 / Python - libeospy 사용
1. POST / Form Data로 파라미터를 불러온다
1. Action의 파라미터를 구성할 때 집어넣는다
1. 실행시키고, 그 결과에 따라 적당한 Response를 삽입한다.

# 2/28 수업 과제
1. Flaks - EOSIO의 연결을, 로컬 EOSIO에서 JungleNet BP로 전환한다
1. 컨트렉트 ABI 업데이트
지금 블록익스플로러가셔 계정을 살펴보면, 실행할 수 있는 액션이 아무것도 없을 것이다.
ABI 파일이 텅 빈채로 만들어졌기 때문에 다시 만들어 Deploy 해야 한다.
