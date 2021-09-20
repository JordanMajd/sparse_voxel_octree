(function () {
  "use strict";

  const canvas = document.getElementById("canvas");

  function QuadTree(x, y, size, pt, value) {
    this.center = point(x, y);
    this.radius = size / 2;
    this.value = value;
    this.point = pt;
    this.children = [ [null, null], [null, null] ];

    drawSquare(this.center, this.radius, "blue");
    console.log(`r${this.radius} x${this.center.x}, y${this.center.y}`);
    if(this.point) {
      // console.log(`${this.point.x}, ${this.point.y}`);
      drawCircle(this.point, 0.5, "red");
    }
  }


  QuadTree.prototype.insert = function (pt, val) {
    if (this.radius <= 0.5) {
      this.value = val;
      this.point = pt;
      return;
    }

    // if leaf node
    if (this.point) {
      const leafVal = this.value;
      const leafPoint = this.point;
      this.value = null;
      this.point = null;
      this.insert(leafPoint, leafVal);
    }

    let xGT = pt.x > this.center.x ? 1 : 0;
    let yGT = pt.y > this.center.y ? 1 : 0;

    let child = this.children[xGT][yGT];
     // if child is leaf node
    //  if(child.value){
    
    if (child) {
      child.insert(pt, val);
    } else {
      // get center of new bounds
      let midX, midY;
      if (xGT) {
        midX = this.center.x + this.radius / 2;
      } else {
        midX = this.center.x - this.radius / 2;
      }
      if (yGT) {
        midY = this.center.y + this.radius / 2;
      } else {
        midY = this.center.y - this.radius / 2;
      }
      this.children[xGT][yGT] = new QuadTree(midX, midY, this.radius, pt, val);
    }
  };

  QuadTree.prototype.find = function (pt) {

    let xGT = pt.x > this.center.x ? 1 : 0;
    let yGT = pt.y > this.center.y ? 1 : 0;
  
    let child = this.children[xGT][yGT];
  
    if(!child){
      return this.value;
    }
    return child.find(pt);
  };

  QuadTree.prototype.coords = function () {
    return point(Math.ceil(this.center.x), Math.ceil(this.center.y));
  }

  function point(x, y) {
    return { x, y };
  }

  function drawSquare(pos, radius, color) {
    const node = document.createElementNS("http://www.w3.org/2000/svg", "rect");
    const translation = `translate(${pos.x - radius}, ${pos.y - radius})`;
    node.setAttribute(
      "transform",
      translation,
    );
    node.setAttribute("fill", color);
    node.setAttribute("fill-opacity", 0.3);
    node.setAttribute("stroke-width", 0.2);
    node.setAttribute("stroke", "#f5f5f6");
    node.setAttribute("stroke-opacity", 1);
    node.setAttribute("width", radius * 2);
    node.setAttribute("height", radius * 2);
    canvas.appendChild(node);
    // node.animate([
    //   { transform: `scale(0) ${translation}` },
    //   { transform: `scale(1) ${translation}` }
    // ],
    // {
    //   duration: 1000,
    //   iterations: 1
    // });
  }

  function drawCircle(pos, radius, color) {
    const node = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    const translation = `translate(${pos.x}, ${pos.y})`
    node.setAttribute(
      "transform",
      translation,
    );
    node.setAttribute("fill", color);
    node.setAttribute("fill-opacity", 0.5);
    node.setAttribute("stroke-width", 0.1);
    node.setAttribute("stroke", "#f5f5f6");
    node.setAttribute("stroke-opacity", 1);
    node.setAttribute("r", radius);
    canvas.appendChild(node);
  }

  const tree = new QuadTree(0, 0, 32, null, null);

  let a = point(-3, -2);
  let b = point(-3, -1);
  let c = point(14, 4);
  let d = point(14, 14);


  tree.insert(a, "a");
  tree.insert(b, "b");
  tree.insert(c, "c");
  tree.insert(d, "d");

  console.log(tree.find(a));
  console.log(tree.find(b));
  console.log(tree.find(c));
  console.log(tree.find(d));
}());
