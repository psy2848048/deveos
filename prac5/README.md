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
