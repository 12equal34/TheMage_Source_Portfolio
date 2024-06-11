# TheMage_Source_Portfolio

The Mage 플레이 영상 유튜브 링크: https://youtu.be/K2QGk7OlUCc

The Mage play test.exe 실행파일(윈도우 전용)이 들어있는 Onedrive 링크: https://1drv.ms/f/s!Aqh-AjiWNIN3pWPJECYEEn5JH3CS?e=zj9VJv

# Core Folders
1. **PaperAnim**: Paper Characters의 Animation을 담당합니다.
2. **Monster**: Monsters의 AI를 담당합니다.

# PaperAnim
>엔진 내의 APaperCharacter는 UPaperFlipbookComponent를 통해 2d Animation을 애니메이션의 전통적인 Flipbook 방법으로 구현합니다.
>이때 UPaperFlipbookComponent의 TickFlipbook 메서드를 사용합니다.
>TickFlipbook에서 SetPlaybackPosition 메서드를 사용하여 현재 캐릭터의 스프라이트(UPaperFlipbook)를 갱신합니다.

APaperAnimCharacter는 APaperCharacter를 상속하고 기존의 UPaperFlipbookComponent의 TickFlipbook를 사용하지 않고,
새롭게 UPaperAnimPlayer를 사용하여 TickPlayback 메서드를 사용하여 애니메이션을 재생합니다. 즉 재생 책임을 UPaperAnimPlayer로 전가하였습니다.

UPaperAnimPlayer는 UPaperFlipbookComponent과 다르게 time 단위가 아닌 frame 단위로 증분하여 재생합니다.
이유는 각 frame key에 해당하는 현재 캐릭터의 스프라이트(UPaperFlipbook)가 끝나거나 시작되었을 때, 이벤트 또는 PlayFrameEffects 메서드 호출을 발생하기 위함입니다.

PlayFrameEffects 메서드는 현재 캐릭터의 스프라이트가 변경되었을 때, frame key에 해당하는 UPaperAnimAsset의 컨테이너 내 원소의 UPaperAnimFrameEffect::Play() 메서드를 호출합니다.
이를 통해 스킬의 스폰, 캐릭터의 질주, 주먹 공격 도중의 방향키 입력으로 인한 이동, 사운드 발생 등을 구현할 수 있었습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/351c333c-35cc-4554-8f5e-59741507d112)

타 프로젝트에서 주로 사용하는 PaperZD 플러그인(2d animation)을 사용하지 않은 이유는 애니메이션 에셋 관리가 불편했기 때문입니다.
그래서 UPaperAnimAsset을 통해 다음과 같이 한 곳에서 애니메이션을 관리할 수 있도록 했습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/f1b9f433-4842-43ac-bf3e-1e6f7efa7ccc)

또한 PaperZD의 애니메이션 그래프가 복잡하고 불편하다고 느꼈습니다.
이를 UFUNCTION(BlueprintNativeEvent) CalculateAnimation 메서드를 통해 블루프린트 노드를 활용하면 더 단순하다고 생각했습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/48f0513b-9d8d-4362-9566-522201ad76a4)

# Monster
게임 내의 몬스터는 AMonsterCharacter를 상속받습니다.
AMonsterCharacter는 몬스터의 AI를 담당하는 UMonsterComponent를 갖고 있습니다.
UMonsterComponent는 (판단)UMonsterBrain, (레이트레이싱 인식)UMonsterSight, (충돌 인식)UMonsterSkin 객체를 하나씩 갖습니다.
상속을 통해 각각의 기관들의 능력을 바꿀 수 있습니다.

UMonsterSight를 통해 주변에 적이 있는지 판단합니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/41ce97a9-f784-498e-9937-f8eb922c21f0)
![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/84ddf1e1-16a2-416a-badc-2495b6bf60ec)

