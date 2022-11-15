window.__require = function t(e, i, n) {
function c(o, a) {
if (!i[o]) {
if (!e[o]) {
var r = o.split("/");
r = r[r.length - 1];
if (!e[r]) {
var u = "function" == typeof __require && __require;
if (!a && u) return u(r, !0);
if (s) return s(r, !0);
throw new Error("Cannot find module '" + o + "'");
}
o = r;
}
var h = i[o] = {
exports: {}
};
e[o][0].call(h.exports, function(t) {
return c(e[o][1][t] || t);
}, h, h.exports, t, e, i, n);
}
return i[o].exports;
}
for (var s = "function" == typeof __require && __require, o = 0; o < n.length; o++) c(n[o]);
return c;
}({
game: [ function(t, e) {
"use strict";
cc._RF.push(e, "d3bcbDPHVNIxZBWHNDimmvK", "game");
cc.Class({
extends: cc.Component,
properties: {
starPrefab: {
default: null,
type: cc.Prefab
},
maxStarDuration: 0,
minStarDuration: 0,
ground: {
default: null,
type: cc.Node
},
player: {
default: null,
type: cc.Node
},
msg: {
default: null,
type: cc.RichText
},
scoreDisplay: {
default: null,
type: cc.Label
},
scoreAudio: {
default: null,
type: cc.AudioClip
}
},
onLoad: function() {
this.groundY = this.ground.y + this.ground.height / 2;
this.timer = 0;
this.starDuration = 0;
this.spawnNewStar();
this.score = 0;
this.msg.node.runAction(cc.fadeOut(3));
},
start: function() {},
update: function(t) {
this.timer += t;
},
spawnNewStar: function() {
var t = cc.instantiate(this.starPrefab);
this.node.addChild(t);
t.setPosition(this.getNewStarPosition());
t.getComponent("star").game = this;
this.starDuration = this.minStarDuration + Math.random() * (this.maxStarDuration - this.minStarDuration);
this.timer = 0;
},
getNewStarPosition: function() {
var t, e = this.groudY + Math.random() * this.player.getComponent("player").jumpHeight + 80, i = this.node.width / 2;
t = 2 * (Math.random() - .5) * i;
return cc.v2(t, e);
},
gainScore: function() {
this.score += 1;
this.scoreDisplay.string = "Score: " + this.score;
cc.audioEngine.playEffect(this.scoreAudio, !1);
}
});
cc._RF.pop();
}, {} ],
player: [ function(t, e) {
"use strict";
cc._RF.push(e, "0d89empaARBhapP6UFIX5xL", "player");
cc.Class({
extends: cc.Component,
properties: {
jumpHeight: 0,
jumpDuration: 0,
maxMoveSpeed: 0,
accel: 0,
jumpAudio: {
default: null,
type: cc.AudioClip
}
},
onLoad: function() {
var t = this.runJumpAction();
cc.tween(this.node).then(t).start();
this.accLeft = !1;
this.accRight = !1;
this.xSpeed = 0;
cc.systemEvent.on(cc.SystemEvent.EventType.KEY_DOWN, this.onKeyDown, this);
cc.systemEvent.on(cc.SystemEvent.EventType.KEY_UP, this.onKeyUp, this);
},
onDestroy: function() {
cc.systemEvent.off(cc.SystemEvent.EventType.KEY_DOWN, this.KEY_DOWN, this);
cc.systemEvent.off(cc.SystemEvent.EventType.KEY_UP, this.onKeyUp, this);
},
start: function() {},
update: function(t) {
this.accLeft ? this.xSpeed -= this.accel * t : this.accRight && (this.xSpeed += this.accel * t);
Math.abs(this.xSpeed) > this.maxMoveSpeed && (this.xSpeed = this.maxMoveSpeed * this.xSpeed / Math.abs(this.xSpeed));
this.node.x += this.xSpeed * t;
},
runJumpAction: function() {
var t = cc.tween().by(this.jumpDuration, {
y: this.jumpHeight
}, {
easing: "sineOut"
}), e = cc.tween().by(this.jumpDuration, {
y: -this.jumpHeight
}, {
easing: "sineIn"
}), i = cc.tween().sequence(t, e).call(this.playJumpSound, this);
return cc.tween().repeatForever(i);
},
playJumpSound: function() {
cc.audioEngine.playEffect(this.jumpAudio, !1);
},
onKeyDown: function(t) {
switch (t.keyCode) {
case cc.macro.KEY.left:
this.accLeft = !0;
console.log("left");
break;

case cc.macro.KEY.right:
this.accRight = !0;
console.log("right");
}
},
onKeyUp: function(t) {
switch (t.keyCode) {
case cc.macro.KEY.left:
this.accLeft = !1;
break;

case cc.macro.KEY.right:
this.accRight = !1;
}
}
});
cc._RF.pop();
}, {} ],
star: [ function(t, e) {
"use strict";
cc._RF.push(e, "7e82aFLIxRAN4njzGmuPEVl", "star");
cc.Class({
extends: cc.Component,
properties: {
pickRadius: 0
},
start: function() {},
update: function() {
if (this.getPlayerDistance() < this.pickRadius) this.onPicked(); else {
var t = 1 - this.game.timer / this.game.starDuration;
this.node.opacity = 50 + Math.floor(205 * t);
}
},
getPlayerDistance: function() {
var t = this.game.player.getPosition();
return this.node.position.sub(t).mag();
},
onPicked: function() {
this.game.spawnNewStar();
this.game.gainScore();
this.node.destroy();
}
});
cc._RF.pop();
}, {} ]
}, {}, [ "game", "player", "star" ]);