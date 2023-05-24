use std::alloc::{handle_alloc_error, Layout};
use std::{alloc, fmt, ptr};

const layout: Layout = Layout::new::<Node>();

#[derive(Copy, Clone, PartialOrd, Eq)]
pub struct Node {
    pub val: i32,
    pub next: *mut Node,
    pub previous: *mut Node,
}

impl Node {
    pub unsafe fn new(val: i32, next: Option<*mut Node>, previous: Option<*mut Node>) -> *mut Node {
        let ptr = alloc::alloc(layout);

        if ptr.is_null() {
            handle_alloc_error(layout);
        }

        let node = ptr as *mut Node;
        (*node).val = val;
        (*node).next = next.unwrap_or(ptr::null_mut());
        (*node).previous = previous.unwrap_or(ptr::null_mut());

        node
    }

    pub fn next(&self) -> *const Node {
        self.next
    }

    pub fn previous(&self) -> *const Node {
        self.previous
    }

    pub fn same_as(&self, other: &Node) -> bool {
        self.val == other.val && self.next == other.next && self.previous == other.previous
    }
}
impl fmt::Debug for Node {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Node")
            .field("val", &self.val)
            .field("next", unsafe { &(*self.next).val })
            .field("previous", unsafe { &(*self.previous).val })
            .finish()
    }
}

impl fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.val)
    }
}

impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        self.val == other.val
    }
}
