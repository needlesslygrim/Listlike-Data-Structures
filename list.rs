use std::fmt::Debug;

struct Node<T> {
    x: T,
    next: Option<*mut Node<T>>,
    previous: Option<*mut Node<T>>,
}

impl<T> Node<T> {
    pub unsafe fn pop_next(&mut self) {
        if let Some(next_node) = self.next {
            drop(next_node);
            self.next = None;
        }
    }
}

impl<T: Debug> Node<T> {
    pub unsafe fn print(&mut self) {
        let current_node: *mut Node<_> = self;

        while !(*current_node.next).is_none() {
            print!("{:#?},", (*current_node).x);
            current_node = current_node.next.unwrap();
        }
    }
}

fn main() {
    unsafe {
        let mut head = Node {
            x: 0,
            next: None,
            previous: None,
        };

        let mut one = Node {
            x: 1,
            next: None,
            previous: Some(&mut head),
        };
        head.next = Some(&mut one);

        head.pop_next();
    }
}
