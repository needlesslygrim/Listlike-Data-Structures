use lists::{list::List, node::Node};
use std::alloc::Layout;

fn main() {
    unsafe {
        let node = Node::new(5, None, None);
        let node2 = Node::new(3, None, Some(node));
        unsafe {
            println!("{}", *node < *node2);
            std::alloc::dealloc(node as *mut u8, Layout::new::<Node>());
            std::alloc::dealloc(node2 as *mut u8, Layout::new::<Node>());
        }
        let arr = [1, 2, 3, 4, 5];
        let list: List = List::from(arr.as_slice());
        let mapped: Vec<i32> = list.into_iter().map(|x| x * 2).collect();
        println!("{:#?}", mapped);
        // println!("{:#?}", list);
    }
    println!("Hello, world!");
}
