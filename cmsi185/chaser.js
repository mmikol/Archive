const canvas = document.querySelector("canvas");
const ctx = canvas.getContext("2d");
let progressBar = document.querySelector("progress");
let timeSpan = document.getElementById("timeSpan");

const CANVAS_DIMENSIONS = {
	top: 0,
	right: canvas.width,
	bottom: canvas.height,
	left: 0
};

const CENTER_OF_CANVAS = {
	x: CANVAS_DIMENSIONS.right / 2,
	y: CANVAS_DIMENSIONS.bottom / 2
};

class Mouse {
	constructor() {
		[this.x, this.y] = [CENTER_OF_CANVAS.x, CENTER_OF_CANVAS.y];
	}
	getMousePos(event) {
		const { left, top } = canvas.getBoundingClientRect();
		this.x = event.clientX - left;
		this.y = event.clientY - top;
	}
}

class Game {
	constructor() {
		this.resetInstruction = "press any key to restart";
		this.resultFont = "bold 50px Courier New";
		this.instructionFont = "italic 20px Courier New";
		this.fontColor = "black";
		this.textAlign = "center";
	}
	drawScene() {
		this.refreshBackground();
		this.spawnSprites();
		this.updateScene();
		this.updateProgress();
		enemies.forEach(enemy => enemy.pushBack(player));
		if (progressBar.value <= 0) {
			this.showLoss();
			this.allowRestart();
		} else {
			requestAnimationFrame(this.drawScene.bind(this));
		}
	}
	refreshBackground() {
		let background = new Image();
		background.src = "https://i.stack.imgur.com/A8BXP.png";
		ctx.drawImage(background, 0, 0, canvas.width, canvas.height);
	}
	spawnSprites() {
		player.draw();
		enemies.forEach(enemy => enemy.draw());
		walls.forEach(wall => wall.draw());
	}
	updateScene() {
		player.chase(mouse);
		if (health.available) {
			health.updateAvailability();
		}
		enemies.forEach((enemy, i) => {
			enemy.chase(player);
			if (timer.seconds !== 0 && timer.seconds % 10 === 0) {
				health.available = true;
			}
			enemy.pushBack(enemies[(i + 1) % enemies.length]);
			walls.forEach((wall, i) => {
				if (player.hasTouched(wall)) {
					player.pushBack(wall);
				}
				if (enemy.hasTouched(wall)) {
					enemy.pushBack(wall);
				}
				if (wall.hasTouched(walls[(i + 1) % walls.length])) {
					wall.pushBack(walls[(i + 1) % walls.length]);
				}
			});
		});
	}
	updateProgress() {
		enemies.forEach(enemy => {
			if (player.hasTouched(enemy)) {
				progressBar.value -= 1;
			}
		});
		if (timer.seconds !== 0 && timer.seconds % 10 === 0) {
			this.available = true;
		}
		timer.showTime();
	}
	showLoss() {
		ctx.font = this.resultFont;
		ctx.fillStyle = this.fontColor;
		ctx.textAlign = this.textAlign;
		ctx.fillText("GAME OVER", CENTER_OF_CANVAS.x, CENTER_OF_CANVAS.y);
		ctx.font = this.instructionFont;
		ctx.fillText(
			this.resetInstruction,
			CENTER_OF_CANVAS.x,
			CENTER_OF_CANVAS.y + 50
		);
	}
	allowRestart() {
		document.addEventListener("keypress", event => {
			this.reset();
		});
	}
	reset() {
		if (progressBar.value === 0) {
			progressBar.value = 100;
			timer.milliseconds = 0;
			timer.seconds = 0;
			health.available = false;
			Object.assign(player, {
				x: CENTER_OF_CANVAS.x,
				y: CENTER_OF_CANVAS.y
			});
			enemies.forEach(enemy => {
				Object.assign(enemy, {
					x: enemy.randomCoordinate() + player.x,
					y: enemy.randomCoordinate() + player.y
				});
			});
			Object.assign(health, {
				x: health.randomCoordinate(),
				y: health.randomCoordinate()
			});
			walls.forEach(wall => {
				Object.assign(wall, {
					x: wall.randomCoordinate(),
					y: wall.randomCoordinate()
				});
			});
			requestAnimationFrame(this.drawScene.bind(this));
		}
	}
}

class Timer {
	constructor() {
		this.milliseconds = 0;
		this.seconds = 0;
	}
	getTime() {
		this.milliseconds++;
		if (this.milliseconds % 100 === 0) {
			this.seconds++;
		}
	}
	showTime() {
		this.getTime();
		timeSpan.innerHTML = this.seconds;
	}	
}

class Sprite {
	constructor() {
		[this.width, this.height] = Array(2).fill(70);
		this.image = new Image();
	}
	draw() {
		ctx.drawImage(
			this.image,
			this.x - this.width / 2,
			this.y - this.height / 2,
			this.width,
			this.height
		);
	}
	randomCoordinate() {
		let max = canvas.width - 50;
		let min = 75;
		return Math.random() * (max - (min + 1)) + min;
	}
	distanceFrom(secondSprite) {
		return Math.hypot(secondSprite.x - this.x, secondSprite.y - this.y);
	}
	hasTouched(secondSprite) {
		return (
			this.x < secondSprite.x + secondSprite.width &&
			this.x + this.width > secondSprite.x &&
			this.y < secondSprite.y + secondSprite.height &&
			this.height + this.y > secondSprite.y
		);
	}
	chase(secondSprite) {
		this.x += (secondSprite.x - this.x) * this.speed;
		this.y += (secondSprite.y - this.y) * this.speed;
	}
	pushBack(secondSprite) {
		let [dx, dy] = [secondSprite.x - this.x, secondSprite.y - this.y];
		const L = Math.hypot(dx, dy);
		let distToMove = this.width - L;
		if (distToMove > 0) {
			dx /= L;
			dy /= L;
			this.x -= dx * distToMove / 2;
			this.y -= dy * distToMove / 2;
			secondSprite.x += dx * distToMove / 2;
			secondSprite.y += dy * distToMove / 2;
		}
	}
}

class Player extends Sprite {
	constructor() {
		super();
		this.playerSpeed = 0.05;
		[this.x, this.y] = [CENTER_OF_CANVAS.x, CENTER_OF_CANVAS.y];
		this.speed = this.playerSpeed;
		this.image.src =
			"https://orig00.deviantart.net/ed98/f/2011/176/2/e/8_bit_custom_ninja_by_lpugh-d3k0gr3.png";
	}
}

class Enemy extends Sprite {
	constructor() {
		super();
		this.enemySpeed = {
			max: 0.03,
			min: 0.001
		};
		[this.x, this.y] = Array.from({ length: 2 }, x => this.randomCoordinate());
		this.speed = this.randomSpeed();
		this.image.src =
			"https://pbs.twimg.com/profile_images/1663329560/kawaii_cupcake_icon__by_ZikittyZaki_400x400.gif";
	}
	randomSpeed() {
		return (
			Math.random() * (this.enemySpeed.max - this.enemySpeed.min) +
			this.enemySpeed.min
		);
	}
}

class Health extends Sprite {
	constructor() {
		super();
		this.available = false;
		[this.x, this.y] = Array.from({ length: 2 }, x => this.randomCoordinate());
		this.image.src =
			"https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRDPqfGvjUrEjr72T1SU8RdljL2pqwJMNhX1jI-eR_kzav-ECy_";
	}
	updateAvailability() {
		this.draw();
		if (this.hasTouched(player)) {
			this.available = false;
			progressBar.value += 50;
		}
	}
}

class Wall extends Sprite {
	constructor() {
		super();
		this.wallDimensions = {
			width: 50,
			height: 150
		};
		[this.x, this.y] = Array(2).fill(this.randomCoordinate());
		[this.width, this.height] = [
			this.wallDimensions.width,
			this.wallDimensions.height
		];
		this.image.src =
			"https://t4.ftcdn.net/jpg/01/32/50/45/240_F_132504556_5IPIR4F4kS4Z0Dw4H99ff4VYfs65m8fh.jpg";
	}
}

const mouse = new Mouse();
const game = new Game();
const timer = new Timer();
const player = new Player();
const enemies = Array.from({ length: 4 }, x => new Enemy());
const health = new Health();
const walls = Array.from({ length: 2 }, x => new Wall());

document.body.addEventListener("mousemove", mouse.getMousePos.bind(mouse));
requestAnimationFrame(game.drawScene.bind(game));
