# 2018_imbedded-dev_car
1. [설치환경](#설치환경)


## 설치환경
1. Python 2.7이상
2. dlib 19.7 이상
3. face_recognition
4. Raspberry Pi 3
5. json-c
### Python 설치
 * [Python 설치법](http://tofusoup429.tistory.com/2)

### dlib & face_recognition on Raspberry Pi 설치
 * [dlib and face_recognition 설치법](https://gist.github.com/ageitgey/1ac8dbe8572f3f533df6269dab35df65)
  위 링크의 모든 과정을 필요로함.
 * dlib를 설치하는데 있어서 19.7이상의 버전을 필요로함. (본 프로젝트에서는 19.9를 사용)
  
### cJSON 설치
 'cJSON' GitHub repo: https://github.com/DaveGamble/cJSON
 
 ```sh
 $ git clone https://github.com/DaveGamble/cJSON
 ```
 
### bluetooth 설치
 bluetooth lib 설치 및 환경설정 참조: http://webnautes.tistory.com/1137?category=699571
```sh
$ sudo apt-get install bluetooth libbluetooth-dev
$ sudo apt-get install bluez
```
 실행시 발생하는 세그멘테에션 폴트(Segmetation Fault)을 위한 SDP Server 활성화 설정 필요.
 * bluetooth server 연결전 페어링과정이 필요함.
 * bluetooth연결이 되는지 확인을 위한 소스가 /test/bluetooth_server.c 에 있음.
