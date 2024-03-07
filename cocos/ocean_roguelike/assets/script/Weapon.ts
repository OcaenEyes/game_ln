import { Vec2, v2 } from 'cc';
/*
 * @Author: OCEAN.GZY
 * @Date: 2024-03-04 17:17:57
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-03-06 23:26:56
 * @FilePath: /ocean_roguelike/assets/script/Weapon.ts
 * @Description: 注释信息
 */
import { _decorator, Component, Node, instantiate, Prefab, RigidBody2D } from 'cc';
import { Global } from './Global';
const { ccclass, property } = _decorator;

@ccclass('Weapon')
export class Weapon extends Component {

    @property(Prefab) bullet: Prefab

    // 以秒为单位的时间间隔
    interval: number = 1;

    start() {
        var cb = function () {
            var firePoint = this.node.getChildByName("FirePoint");
            Global.weaponBullets.worldPosition = firePoint.worldPosition;
            var _bullet = instantiate(this.bullet);
            Global.weaponBullets.addChild(_bullet);
        };
        this.schedule(cb, this.interval);
    }

    update(deltaTime: number) {
    }

}

