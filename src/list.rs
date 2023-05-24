use std::alloc::alloc;
use std::fmt::Formatter;
use std::{alloc, fmt, iter, ops, ptr};

use crate::node::Node;

#[derive(Ord, PartialOrd, Eq)]
pub struct List {
    pub(crate) len: usize,
    pub(crate) head: *mut Node,
    pub(crate) tail: *mut Node,
}

impl List {
    pub fn new() -> Self {
        Self {
            len: 0,
            head: ptr::null_mut(),
            tail: ptr::null_mut(),
        }
    }

    pub fn get(&self) -> *const Node {
        ptr::null_mut()
    }
    pub fn head(&self) -> *const Node {
        self.head
    }
    pub fn tail(&self) -> *const Node {
        self.tail
    }
    pub fn len(&self) -> usize {
        self.len
    }

    pub fn push(&mut self, val: i32) {
        unsafe {
            let ptr = alloc::alloc(alloc::Layout::new::<Node>());
            let node: *mut Node = ptr as *mut Node;
            (*node).val = val;
            (*self.tail).next = node;
            self.tail = node;
            self.len += 1;
        }
    }
    pub fn insert(index: usize, val: i32) {
        unimplemented!()
    }
    pub fn pop() -> i32 {
        unimplemented!()
    }
    pub fn remove(index: usize) -> i32 {
        unimplemented!()
    }
}

impl From<&[i32]> for List {
    fn from(vals: &[i32]) -> Self {
        if vals.len() == 0 {
            return List::new();
        }

        let mut list = List::new();
        list.len = vals.len();
        unsafe {
            list.head = Node::new(*vals.first().unwrap(), None, None);
            if vals.len() == 1 {
                return list;
            }
            let mut previous_node = Node::new(vals[1], None, Some(list.head));
            (*list.head).next = previous_node;

            for i in &vals[2..] {
                let node = Node::new(*i, None, Some(previous_node));

                (*previous_node).next = node;
                previous_node = node;
            }

            list.tail = previous_node;
        }
        list
    }
}

impl Drop for List {
    fn drop(&mut self) {
        if self.len == 0 {
            return;
        } else if self.len == 1 {
            let head = self.head;
            let ptr = head as *mut u8;
            unsafe { alloc::dealloc(ptr, alloc::Layout::new::<Node>()) }
        }

        let mut current_node = self.head;
        unsafe {
            let mut next_node = (*current_node).next;
            while !next_node.is_null() {
                alloc::dealloc(current_node as *mut u8, alloc::Layout::new::<Node>()); // FIXME: extract this Layout into a new variable/constant
                current_node = next_node;
                next_node = (*next_node).next;
            }

            alloc::dealloc(current_node as *mut u8, alloc::Layout::new::<Node>());
        }
    }
}

impl ops::Index<usize> for List {
    type Output = i32;

    fn index(&self, index: usize) -> &Self::Output {
        if index >= self.len {
            panic!(
                "index({}) not in range, should be < len({})",
                index, self.len
            );
        }
        if index == 0 {
            return unsafe { &((*self.head).val) };
        }

        let mut current_node = self.head;

        for i in 0..index {
            current_node = unsafe { (*current_node).next };
        }

        return unsafe { &(*current_node).val };
    }
}

// impl ops::Deref for List {
//     type Target = [i32];
//     fn deref(&self) -> &Self::Target {
//         unsafe { [3] }
//     }
// }

impl IntoIterator for List {
    type Item = i32;
    type IntoIter = IntoIter;

    fn into_iter(self) -> Self::IntoIter {
        IntoIter {
            index: 0,
            list: self,
        }
    }
}

pub struct IntoIter {
    index: usize,
    list: List,
}
impl Iterator for IntoIter {
    type Item = i32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.index > self.list.len {
            None
        } else {
            Some(self.list[self.index - 1])
        }
    }
}
impl fmt::Debug for List {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        if self.len == 0 {
            return write!(f, "()");
        } else if self.len == 1 {
            return write!(f, "({})", unsafe { (*self.head).val });
        }

        let _ = write!(f, "({}, ", unsafe { (*self.head).val })?;
        unsafe {
            let mut current_node = (*self.head).next;

            while (*current_node).next != ptr::null_mut() {
                let _ = write!(f, "{}, ", (*current_node).val);
                current_node = (*current_node).next;
            }

            writeln!(f, "{})", (*current_node).val)
        }
    }
}

impl PartialEq for List {
    fn eq(&self, other: &Self) -> bool {
        if self.len != other.len {
            return false;
        } else if self.len == 0 {
            return true;
        }
        let mut current_self = self.head;
        let mut current_other = other.head;
        unsafe {
            if (*current_self).val != (*current_other).val {
                return false;
            }
            while !(*current_self).next.is_null() {
                current_self = (*current_self).next;
                current_other = (*current_other).next;
                if (*current_self).val != (*current_other).val {
                    return false;
                }
            }
            if (*current_self).val != (*current_other).val {
                return false;
            }
        }

        true
    }
}
